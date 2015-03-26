/*--------------------------------------------------------------------------------------------
-- SOURCE FILE:		server.cpp 		An application that reads, processes, and echoes data out
--									to clients.
--
-- PROGRAM:			Linux Chat
--
-- FUNCTIONS:
--					int main()
--
-- DATE:			March 20, 2015
--
-- REVISIONS:
--
-- DESIGNER:		Sebastian Pelka
--
-- PROGRAMMER:		Sebastian Pelka
--					Filip Gutica
--
-- NOTES:
-- based on code found at www.milliways.bcit.ca/c4981, by Aman Abdulla
--
----------------------------------------------------------------------------------------------*/

#include "server.h"

int listen_socket;
int max_filedescriptors;			//the number of file descriptors used
int num_ready_descriptors;
int max_array_index = -1;
int clients[FD_SETSIZE];
fd_set master_filedescriptors;		//the master set of file descriptors
fd_set copy_filedescriptors;		//holds a copy of the master set
vector<string> userList;


/*--------------------------------------------------------------------------------------------
-- FUNCTION:	main
--
-- DATE:		March 20, 2015
--
-- REVISIONS:
--
-- DESIGNER: 	Sebastian Pelka
--
-- PROGRAMMER:	Sebastian Pelka
--
-- INTERFACE:	int main ()
--
-- RETURNS:		returns 1 if the function fails, 0 if succesful
--
-- NOTES:		the main entry point the LinuxChat program. Initializes the listening socket.
----------------------------------------------------------------------------------------------*/
int main ()
{
	struct sockaddr_in listen_address;

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
	int retval = setsockopt ( listen_socket, SOL_SOCKET, SO_REUSEADDR, &arg, sizeof(arg) );
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

	for (int i = 0; i < FD_SETSIZE; i++)
           	clients[i] = -1;             // -1 indicates available entry

	//initialize the master file descriptor set and add the listen socket to it
	FD_ZERO( &master_filedescriptors );
	FD_SET( listen_socket, &master_filedescriptors );

	processConnections();


	return 0;
}

/*--------------------------------------------------------------------------------------------
-- FUNCTION:	processConnections
--
-- DATE:		March 20, 2015
--
-- REVISIONS:
--
-- DESIGNER: 	Sebastian Pelka
--
-- PROGRAMMER:	Sebastian Pelka
--
-- INTERFACE:	int processConnections()
--
-- RETURNS:		returns 1 if the function fails
--
-- NOTES:		this function is used to initialize file descriptors for reading and writing
--
----------------------------------------------------------------------------------------------*/
int processConnections()
{

	//go into a forever loop
	for (;;)
	{
		//copy the master fd set to a new variable
		copy_filedescriptors = master_filedescriptors;

		//call select to monitor multiple file descriptors
		num_ready_descriptors = select ( ( max_filedescriptors + 1 ), &copy_filedescriptors, NULL, NULL, NULL );

		if ( num_ready_descriptors == -1 )
		{
			//select failure
			std::cout << "ERROR: Select call failed" << std::endl;
			return 1;
		}

		listenNewConnections();

		checkForData();
	}
	return 0;
}

/*--------------------------------------------------------------------------------------------
-- FUNCTION:	listenNewConnections
--
-- DATE:		March 20, 2015
--
-- REVISIONS:
--
-- DESIGNER: 	Sebastian Pelka
--
-- PROGRAMMER:	Sebastian Pelka
--
-- INTERFACE:	void listenNewConnections()
--
-- RETURNS:		void
--
-- NOTES:		listens for new connections on the listening socket, creates a socket, and adds
--				it to an array of sockets. Updates file descriptors as well.
--
----------------------------------------------------------------------------------------------*/
void listenNewConnections()
{
	int client_socket;
	unsigned int client_address_size;
	struct sockaddr_in client_address;

	//variables dealing with reading and echoing
	int i = 0;

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
			
		}

		if ( i > max_array_index )
		{
			//update max index in array
			max_array_index = i;
		}


		if ( --num_ready_descriptors <= 0 )
		{
			//no more descriptors ready
		}
	}
}

/*--------------------------------------------------------------------------------------------
-- FUNCTION:	checkForData
--
-- DATE:		March 20, 2015
--
-- REVISIONS:
--
-- DESIGNER: 	Sebastian Pelka
--
-- PROGRAMMER:	Sebastian Pelka
--
-- INTERFACE:	void listenNewConnections()
--
-- RETURNS:		void
--
-- NOTES:		listens for new connections on the listening socket, creates a socket, and adds
--				it to an array of sockets. Updates file descriptors as well.
--
----------------------------------------------------------------------------------------------*/
void checkForData()
{
	int command;
	int sockFd;
	char* byte_pointer;
	int bytes_to_read;
	int bytes_read;
	char read_buffer[BUFFER_LENGTH];
	memset(read_buffer, 0, sizeof(read_buffer));

	//check for any new data
	for ( int i = 0 ; i <= max_array_index ; i++ )
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
				close(sockFd);
				FD_CLR(sockFd, &master_filedescriptors);
				clients[i] = -1;

				sprintf(read_buffer, "%s", "client disconnected"); // Leave this here
			}

			//echo data to all connected clients
			std::cout << "broadcasting message: " << read_buffer << std::endl;
			for ( i = 0 ; i < FD_SETSIZE ; i++ )
			{
				//do not send the message back to the sender
				if ( sockFd != clients[i] )
				{
					write ( clients[i], read_buffer, BUFFER_LENGTH );
				}
			}

			command = processUsrName(read_buffer);
			if (command == SEND_LIST)
			{
				for (int j = 0; j < userList.size(); j++)
				{
					char temp[BUFFER_LENGTH];
					sprintf(temp, "add:%s", userList[j].c_str());
					for ( i = 0 ; i < clients[i] ; i++ )
							write(clients[i], temp, BUFFER_LENGTH);
				}
			}

			memset(read_buffer, 0, sizeof(read_buffer));

			if (--num_ready_descriptors <= 0)
        			break;
		}
	}
}

/*--------------------------------------------------------------------------------------------
-- FUNCTION:	processUsrName
--
-- DATE:		March 20, 2015
--
-- REVISIONS:
--
-- DESIGNER: 	Filip Gutica
--
-- PROGRAMMER:	Filip Gutica
--
-- INTERFACE:	int processUsrName(char* s)
--
-- RETURNS:		void
--
-- NOTES:		tokenizes a message by user name to update the user list
--
----------------------------------------------------------------------------------------------*/
int processUsrName(char* s)
{

	char *tok;
	tok = (char*)malloc(BUFFER_LENGTH);

	tok = strtok(s, ":");

	if (strcmp(tok, "add") == 0)
	{
		tok = strtok(NULL, ":");
		string usr = tok;
		userList.push_back(usr);

		cout << "Adding to vector: " << usr << endl;

		return SEND_LIST;	
	}
	else if (strcmp(tok, "remove") == 0)
	{
		tok = strtok(NULL, ":");
		for ( int j = 0; j < userList.size(); j++ )
		{
			if (strcmp(userList[j].c_str(), tok) == 0)
			{
				cout << "Removing user: " << tok << endl;
				userList.erase(userList.begin() + j);
			}
		}
	}

	return 0;
}