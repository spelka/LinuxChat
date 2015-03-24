#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <strings.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>

using namespace std;

#define DEFAULT_PORT 7000
#define MAX_CLIENTS 5
#define BUFFER_LENGTH 255

//socket handling variables
int listen_socket, client_socket, sockFd;
int retval;							//holds a return value for testing failures
struct sockaddr_in listen_address, client_address;
unsigned int client_address_size;


// file descriptor handling variables
int max_filedescriptors;			//the number of file descriptors used
fd_set master_filedescriptors;		//the master set of file descriptors
fd_set copy_filedescriptors;		//holds a copy of the master set
int clients[FD_SETSIZE];

//variables dealing with reading and echoing
int i = 0;
int max_array_index = -1;

char* byte_pointer;
int bytes_to_read;
int bytes_read;
char read_buffer[BUFFER_LENGTH];

//prototypes

int processConnections();

int main ()
{
	
	//start server
	//create a stream socket
	listen_socket = socket(AF_INET, SOCK_STREAM, 0);

	if ( listen_socket == -1 )
	{
		//failed to create socket
		std::cout << "ERROR: failed to create socket" << std::endl;
		return 1;
	}

	//set SO_REUSEADDR for the listen socket
	int arg = 1;
	retval = setsockopt ( listen_socket, SOL_SOCKET, SO_REUSEADDR, &arg, sizeof(arg) );
	if ( retval == -1 )
	{
		//set socket option failure
		std::cout << "ERROR: Socket option failure" << std::endl;
		return 1;
	}

	//set up a address structure
	bzero( (char*) &listen_address, sizeof( struct sockaddr_in ) );
	listen_address.sin_family = AF_INET;
	listen_address.sin_port = htons( DEFAULT_PORT );
	listen_address.sin_addr.s_addr = htonl ( INADDR_ANY );

	//bind the socket to accept connections from any ip address
	retval = bind( listen_socket, ( struct sockaddr* ) &listen_address, sizeof( listen_address ) );
	if ( retval == -1 )
	{	
		//bind failed
		std::cout << "ERROR: Failed to bind socket" << std::endl;
		return 1;
	}

	//listen for connections
	listen( listen_socket, 5 );

	//set the largest file descriptor
	max_filedescriptors = listen_socket;

	for (i = 0; i < FD_SETSIZE; i++)
           	clients[i] = -1;             // -1 indicates available entry

	//initialize the master file descriptor set and add the listen socket to it
	FD_ZERO( &master_filedescriptors );
	FD_SET( listen_socket, &master_filedescriptors );

	processConnections();

	
	return 0;
}

int processConnections()
{
	//go into a forever loop
	for (;;)
	{
		//copy the master fd set to a new variable
		copy_filedescriptors = master_filedescriptors;

		//call select to monitor multiple file descriptors
		int num_ready_descriptors = select ( ( max_filedescriptors + 1 ), &copy_filedescriptors, NULL, NULL, NULL );
		
		if ( num_ready_descriptors == -1 )
		{
			//select failure
			std::cout << "ERROR: Select call failed" << std::endl;
			return 1;
		}

		//check for any new connections
		if (FD_ISSET(listen_socket, &copy_filedescriptors))
		{
			//accept the new socket request
			client_address_size = sizeof ( client_address );
			client_socket = accept ( listen_socket, (struct sockaddr *) &client_address, &client_address_size );
			if ( client_socket == -1)
			{
				//failed to accept socket
				std::cout << "ERROR: accept call failed" << std::endl;
				continue;
			}
			
			//message
			std::cout << "New socket accepted. Client address: " << inet_ntoa(client_address.sin_addr) << std::endl;

			//add the new socket to the file descriptor set
			for ( i = 0 ; i < FD_SETSIZE ; i++ )
			{
				if ( clients[i] < 0 )
				{
					//save the descriptor
					clients[i] = client_socket;
					//std::cout << "New client saved. Socket number: " << clients[i] << std::endl;
					break;
				}
			}

			if (i == FD_SETSIZE)
			{
				std::cout << "Too many clients" << std::endl;
				exit(1);
			}
			//add the descriptor to the set
			FD_SET ( client_socket, &master_filedescriptors );

			if ( client_socket > max_filedescriptors )
			{
				//update max_filedescriptors
				max_filedescriptors = client_socket;
				//std::cout << "new max filedescriptors value: " << max_filedescriptors << std::endl;
			}

			if ( i > max_array_index )
			{
				//update max index in array
				max_array_index = i;
				//std::cout << "new max array index: " << max_array_index << std::endl;
			}


			if ( --num_ready_descriptors <= 0 )
			{
				//no more descriptors ready
				//std::cout << "no more descriptors available" << std::endl;
				continue;
			}
			
			
		}


		//check for any new data
		for ( i = 0 ; i <= max_array_index ; i++ )
		{
			//if the socket has no data, skip it
			if ( (sockFd = clients[i]) < 0 )
			{
				continue;
			}

			//check for data
			if ( FD_ISSET ( sockFd, &copy_filedescriptors ) )
			{

				std::cout << "file descriptor is set" << std::endl;
				byte_pointer = read_buffer;
				bytes_to_read = BUFFER_LENGTH;

				//read data in
			    bytes_read = read ( sockFd, byte_pointer, bytes_to_read );
				
				if (bytes_read == 0)
				{
					std::cout << "Remote Address: " << inet_ntoa(client_address.sin_addr) << " closed connection" << std::endl;
					close(sockFd);
					FD_CLR(sockFd, &master_filedescriptors);
					clients[i] = -1;

					sprintf(read_buffer, "%s", "client disconnected");
				}



				//echo data to all connected clients
				std::cout << "broadcasting message: " << read_buffer << std::endl;
				for ( i = 0 ; i < clients[i] ; i++ )
				{
					//do not send the message back to the sender
					if ( sockFd != clients[i] )
					{
						write ( clients[i], read_buffer, BUFFER_LENGTH );
					}
				}

				memset(read_buffer, 0, sizeof(read_buffer));

				if (--num_ready_descriptors <= 0)
            			break;  
			}
		}
	}

	return 0;
}

