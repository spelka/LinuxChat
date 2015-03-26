#ifndef SERVERFUNC_H
#define SERVERFUNC_H

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
#include <vector>

using namespace std;

#define DEFAULT_PORT 7000
#define MAX_CLIENTS 5
#define BUFFER_LENGTH 1024
#define SEND_LIST 1

int processConnections();
int processUsrName(char*);
void listenNewConnections();
void checkForData();

#endif