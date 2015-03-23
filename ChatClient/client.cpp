#include "client.h"
#include "ui_application.h"
#include "application.h"

Application *mainWindow;
int clientSocket;

void ConnectToServer(int port, QString ip, void *app)
{
    struct hostent	*hostPtr;
    struct sockaddr_in serv_addr;

    if (clientSocket = socket(AF_INET, SOCK_STREAM, 0) == -1)
    {
        qDebug() << "Cannot create socket";
        return;
    }




}
