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


    bzero((char *)&serv_addr, sizeof(struct sockaddr_in));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    if ((hostPtr = gethostbyname(ip.toUtf8().constData())) == NULL)
    {
        qDebug() << "Unknown server address";
        return;
    }

    bcopy(hostPtr->h_addr, (char *)&serv_addr.sin_addr, hostPtr->h_length);


}
