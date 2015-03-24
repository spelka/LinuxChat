#include "application.h"
#include "ui_application.h"

Application::Application(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Application)
{
    ui->setupUi(this);

    ui->listUsers->setEditTriggers(QAbstractItemView::NoEditTriggers);

    connect(this, SIGNAL(valueChangedConvo(QString)), ui->txtConvo, SLOT(append(QString)));
    connect(this, SIGNAL(valueChangedUsr(QString)), this, SLOT(addToList(QString)));
    connect(this, SIGNAL(valueUsrRemoved(int)), this, SLOT(removeFromList(int)));
}

Application::~Application()
{
    CloseConnection();
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

        ConnectToServer(portnum, (char*)host.toUtf8().constData(), (void*) this);
    }

}

void Application::appendMessage(QString str)
{
    emit valueChangedConvo(str);
}

void Application::addUser(QString str)
{
    emit valueChangedUsr(str);
}

void Application::removeUser(int index)
{
    emit valueUsrRemoved(index);
}

/**
 * @brief Application::addToList
 * @param str
 */
void Application::addToList(QString str)
{
    usrList.push_back(str);

    ui->listUsers->setModel(new QStringListModel(QList<QString>::fromVector(usrList)));
}

/**
 * @brief Application::removeFromList
 * @param index
 */
void Application::removeFromList(int index)
{
    usrList.remove(index);

    ui->listUsers->setModel(new QStringListModel(QList<QString>::fromVector(usrList)));
}


void Application::on_btnSend_clicked()
{
    QString text = ui->msgEdit->toPlainText();
    int size = text.size();

    SendMessage(text.toUtf8().constData(), size);
}
