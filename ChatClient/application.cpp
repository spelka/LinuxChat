#include "application.h"
#include "ui_application.h"

Application::Application(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Application)
{
    ui->setupUi(this);
}

Application::~Application()
{
    delete ui;
}

void Application::on_actionConnect_to_server_triggered()
{
    QString port;
    QString host;
    int portnum;

    Dialog configureDialog;

    configureDialog.setModal(true);

    if (configureDialog.exec() == QDialog::Accepted)
    {
        port = configureDialog.getPort();
        host = configureDialog.getHost();

        portnum = atoi(port.toUtf8().constData());

        ConnectToServer(portnum, host, (void*) this);
    }

}
