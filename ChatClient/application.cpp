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
    connect(this, SIGNAL(valueUsrRemoved(QString)), this, SLOT(removeFromList(QString)));
}

Application::~Application()
{
    QString str;
    str = QString("remove: %1").arg(displayName);

    SendMessage(str.toUtf8().constData(), str.size());

    CloseConnection();
    delete ui;
}

void Application::on_actionConnect_to_server_triggered()
{
    QString port;
    QString host;
    QString user;
    int portnum;

    Dialog configureDialog;

    configureDialog.setModal(true);

    if (configureDialog.exec() == QDialog::Accepted)
    {
        port = configureDialog.getPort();
        host = configureDialog.getHost();
        displayName = configureDialog.getDisplayName();

        portnum = atoi(port.toUtf8().constData());

        ConnectToServer(portnum, (char*)host.toUtf8().constData(), (void*) this);

        user = QString("add: %1").arg(displayName);

        SendMessage(user.toUtf8().constData(), user.size());
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

void Application::removeUser(QString usr)
{
    emit valueUsrRemoved(usr);
}

/**
 * @brief Application::addToList
 * @param str
 */
void Application::addToList(QString str)
{
    if (!usrList.contains(str))
    {
        usrList.push_back(str);

        ui->listUsers->setModel(new QStringListModel(QList<QString>::fromVector(usrList)));
    }
}

/**
 * @brief Application::removeFromList
 * @param index
 */
void Application::removeFromList(QString usr)
{
    if (usrList.contains(usr))
    {
        usrList.removeOne(usr);
    }

    ui->listUsers->setModel(new QStringListModel(QList<QString>::fromVector(usrList)));
}


void Application::on_btnSend_clicked()
{
    QString text;

    text = QString("usr:%1:%2").arg(displayName).arg(ui->msgEdit->toPlainText());

    int size = text.size();

    appendMessage("Me: " + ui->msgEdit->toPlainText());

    SendMessage(text.toUtf8().constData(), size);
}
