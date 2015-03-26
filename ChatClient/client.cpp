/*****************************************************************************************************
**	SOURCE FILE:	client.cpp 			File for client network operations.
**
**	PROGRAM:	ChatClient
**
**	FUNCTIONS:
**		void ConnectToServer(int, char*, void*)
**		void* readThrd(void*)
**		void SendMessage(const char*, int)
**      void CloseConnection()
**
**
**	DATE: 		March 25, 2015
**
**
**	DESIGNER: 	Filip Gutica A00781910
**
**	PROGRAMMER: Filip Gutica A00781910
**
*********************************************************************************************************/
#include "client.h"
#include "ui_application.h"
#include "application.h"

Application *mainWindow;

int clientSocket;

/*******************************************************************************************************
** Function: 	ConnectToServer(int, char*, void*)
**
** DATE:		March 25, 2015
**
** DESIGNER:	Filip Gutica A00781910
**
** PROGRAMMER:	Filip Gutica A00781910
**
** INTERFACE:	ConnectToServer(int, char*, void*)
**
** RETURNS:
**      void
**
** NOTES:
** Connects to the server using the provided port and ip address. Starts thread to facilitate
** reading on the socket.
******************************************************************************************************/
void ConnectToServer(int port, char *ip, void *app)
{
    QString strInfo;
    struct hostent	*hostPtr;
    struct sockaddr_in serv_addr;
    char **pptr;
    char serverAddress[IP_LEN];
    pthread_t threadRead;

    mainWindow = (Application*) app;


    if ((clientSocket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        qDebug() << "Cannot create socket";
        return;
    }

    qDebug() << "Connecting to ip: " << ip << " Port: " << port;


    bzero((char *)&serv_addr, sizeof(struct sockaddr_in));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    if ((hostPtr = gethostbyname(ip)) == NULL)
    {
        qDebug() << "Unknown server address";
        return;
    }

    bcopy(hostPtr->h_addr, (char *)&serv_addr.sin_addr, hostPtr->h_length);

    if (connect (clientSocket, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
    {
        perror("connect");
        return;
    }


    qDebug() << "Connected: Server Name: " << hostPtr->h_name;

    strInfo = QString("Connected to chatroom server: %1")
            .arg(inet_ntop(hostPtr->h_addrtype, pptr, serverAddress, sizeof(serverAddress)));
    mainWindow->appendMessage(strInfo);

    pthread_create (&threadRead, NULL, readThrd, (void*)1);
    qDebug() << "Pthread created";

}

/*******************************************************************************************************
** Function: 	readThrd(void*)
**
** DATE:		March 25, 2015
**
** DESIGNER:	Filip Gutica A00781910
**
** PROGRAMMER:	Filip Gutica A00781910
**
** INTERFACE:	readThrd(void*)
**
** RETURNS:
**      void*
**
** NOTES:
** PThread function that handles reading on the socket.
******************************************************************************************************/
void* readThrd(void *param)
{
    char *bp, buf[BUFFSIZE];
    int bytes_to_read, n;
    char *tok;
    tok = (char*)malloc(BUFFSIZE);

    QRegExp rxUsrAdd("add: *");
    QRegExp rxUsrRemove("remove: *");
    QRegExp rxMsg("usr: *");

    QString str;

    while(true)
    {
        bp = buf;
        bytes_to_read = BUFFSIZE;    QRegExp rxUsrAdd("add: *");
        n = recv(clientSocket, bp, bytes_to_read, 0);

        if (rxUsrAdd.indexIn(buf) != -1)
        {
            tok = strtok(buf, ":");
            tok = strtok(NULL, ":");
            qDebug() << "User Arrived: " << tok;
            str = tok;
            mainWindow->addUser(str);
        }
        else if (rxUsrRemove.indexIn(buf) != -1)
        {

            tok = strtok(buf, ":");
            tok = strtok(NULL, ":");
            qDebug() << "User left: " << tok;
            str = tok;
            mainWindow->removeUser(str);
        }
        else if (rxMsg.indexIn(buf) != -1)
        {
            tok = strtok(buf, ":");
            tok = strtok(NULL, ":");
            str = tok;
            tok = strtok(NULL, ":");
            str.append(": ");
            str.append(tok);
            mainWindow->appendMessage(str);
        }
    }
}

/*******************************************************************************************************
** Function: 	SendMessage(const char*, int)
**
** DATE:		March 25, 2015
**
** DESIGNER:	Filip Gutica A00781910
**
** PROGRAMMER:	Filip Gutica A00781910
**
** INTERFACE:	SendMessage(const char*, int)
**
** RETURNS:
**      void
**
** NOTES:
** Sends a message on the socket
******************************************************************************************************/
void SendMessage(const char* msg, int size)
{
    send (clientSocket, msg, size, 0);
}

/*******************************************************************************************************
** Function: 	CloseConnection()
**
** DATE:		March 25, 2015
**
** DESIGNER:	Filip Gutica A00781910
**
** PROGRAMMER:	Filip Gutica A00781910
**
** INTERFACE:	CloseConnection()
**
** RETURNS:
**      void
**
** NOTES:
** Closes the socket
******************************************************************************************************/
void CloseConnection()
{
    close(clientSocket);
}
