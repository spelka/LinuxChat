/*****************************************************************************************************
**	SOURCE FILE:	client.h 			header file for client.cpp
**
**	PROGRAM:	ChatClient

**
**	DATE: 		March 25, 2015
**
**
**	DESIGNER: 	Filip Gutica A00781910
**
**	PROGRAMMER: Filip Gutica A00781910
**
*********************************************************************************************************/
#ifndef CLIENT
#define CLIENT

#define IP_LEN 16
#define BUFFSIZE 1024

#include <stdio.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <stdlib.h>
#include <strings.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <QString>
#include <QDebug>
#include <QRegExp>

void ConnectToServer(int port, char* ip, void *app);
void CloseConnection();
void SendMessage(const char*, int);
void* readThrd(void *param);

#endif // CLIENT

