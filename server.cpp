#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <strings.h>
#include <arpa/inet.h>
#include <unistd.h>

#define DEFAULT_PORT 7000
#define MAX_CLIENTS 5
#define BUFFER_LENGTH 255

int main ()
{
	//socket handling variables
	int listen_socket, client_socket;
	int retval;							//holds a return value for testing failures
	struct sockaddr_in listen_address, client_address;
	unsigned int client_address_size;


	// file descriptor handling variables
	int max_filedescriptors;			//the number of file descriptors used
	fd_set master_filedescriptors;		//the master set of file descriptors
	fd_set copy_filedescriptors;		//holds a copy of the master set
	int clients[MAX_CLIENTS];

	//variables dealing with reading and echoing
	int i = 0;
	int max_array_index = -1;

	char* byte_pointer;
	int bytes_to_read;
	int bytes_read;
	char read_buffer[BUFFER_LENGTH];
	
	//start server
	//create a stream socket
	listen_socket = socket(AF_INET, SOCK_STREAM, 0);

	if ( listen_socket == -1 )
	{
		//failed to create socket
		return 1;
	}

	//set SO_REUSEADDR for the listen socket
	int arg = 1;
	retval = setsockopt ( listen_socket, SOL_SOCKET, SO_REUSEADDR, &arg, sizeof(arg) );
	if ( retval == -1 )
	{
		//set socket option failure
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
		return 1;
	}

	//listen for connections
	listen( listen_socket, 5 );

	//set the largest file descriptor
	max_filedescriptors = listen_socket;

	//initialize the master file descriptor set and add the listen socket to it
	FD_ZERO( &master_filedescriptors );
	FD_SET( listen_socket, &master_filedescriptors );

	//do work

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
			}

			//add the new socket to the file descriptor set
			for ( i = 0 ; i < MAX_CLIENTS ; i++ )
			{
				if ( clients[i] < 0 )
				{
					//save the descriptor
					clients[i] = client_socket;
					break;
				}
			}

			if ( i == FD_SETSIZE )
			{
				//too many clients
			}
			else
			{
				//add the descriptor to the set
				FD_SET ( client_socket, &master_filedescriptors );

				if ( client_socket > max_filedescriptors )
				{	
					//update max_filedescriptors
					max_filedescriptors = client_socket;
				}

				if ( i < max_array_index )
				{
					//update max index in array
					max_array_index = i;
				}

				if ( --num_ready_descriptors <= 0 )
				{
					//no more descriptors ready
					continue;
				}
			}
		}

		//check for any new data
		for ( i = 0 ; i <= max_array_index ; i++ )
		{
			//if the socket has no data, skip it
			if ( (client_socket = clients[i]) < 0 )
			{
				continue;
			}

			//??
			if ( FD_ISSET ( client_socket, &copy_filedescriptors ) )
			{
				byte_pointer = read_buffer;
				bytes_to_read = BUFFER_LENGTH;

				//read data in
				while ( ( bytes_read = read ( client_socket, byte_pointer, bytes_to_read ) ) > 0 )
				{
						byte_pointer += bytes_read;
						bytes_to_read -= bytes_read;
				}

				//echo data to all connected clients
				for ( i = 0 ; i < clients[i] ; i++ )
				{
					write ( clients[i], read_buffer, BUFFER_LENGTH );
				}
			}
		}
	}
	return 0;
}