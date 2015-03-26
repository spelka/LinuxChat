/*****************************************************************************************************
**	SOURCE FILE:	application.cpp 			UI Class for our client.
**
**	PROGRAM:	ChatClient
**
**  CONSTRUCTOR:
**      Applicaion(QWidget*)
**
**  DESTRUCTOR:
**      ~Application()
**
**	FUNCTIONS:
**		void on_actionConnect_to_server_triggered()
**		void appendMessage(QString)
**		void addUser(QString)
**      void removeUser(QString)
**      void addToList(QString)
**      void removeFromList(QString)
**      void on_btnSend_clicked()
**      void onReturnPressed()
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
#include "application.h"
#include "ui_application.h"
#include <QFile>
#include <QDateTime>

/*******************************************************************************************************
** Function: 	Application
**
** DATE:		March 25, 2015
**
** DESIGNER:	Auto Generated
**
** PROGRAMMER:	Auto Generated && Filip Gutica A00781910
**
** INTERFACE:	Application(QWidget)
**
**
** NOTES:
** Constructor for our ChatClient GUI. Constructs the ui, initializes UI objects, connects the necesarry
** signals with their corresponding slots which will catch the signal.
**
******************************************************************************************************/
Application::Application(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Application)
{
    ui->setupUi(this);

    ui->listUsers->setEditTriggers(QAbstractItemView::NoEditTriggers);

    connect(this, SIGNAL(valueChangedConvo(QString)), ui->txtConvo, SLOT(append(QString)));
    connect(this, SIGNAL(valueChangedUsr(QString)), this, SLOT(addToList(QString)));
    connect(this, SIGNAL(valueUsrRemoved(QString)), this, SLOT(removeFromList(QString)));
    connect(ui->msgEdit, SIGNAL(returnPressed()), this, SLOT(onReturnPressed()));
}

/*******************************************************************************************************
** Function: 	~Application
**
** DATE:		March 25, 2015
**
** DESIGNER:	Auto Generated
**
** PROGRAMMER:	Autp Generated && Filip Gutica A00781910
**
** INTERFACE:	~Application()
**
**
** NOTES:
** Destructor for our ChatClient GUI. Cleans up the ui, deletes UI objects, Sends message to the server
** telling it to remove this user from the user list. Server will instruct all other clients to do the same
**
******************************************************************************************************/
Application::~Application()
{
    QString str;
    str = QString("remove: %1").arg(displayName);

    SendMessage(str.toUtf8().constData(), str.size());

    CloseConnection();
    delete ui;
}

/*******************************************************************************************************
** Function: 	on_actionConnect_to_server_triggered()
**
** DATE:		March 25, 2015
**
** DESIGNER:	Auto Generated
**
** PROGRAMMER:	Filip Gutica A00781910
**
** INTERFACE:	on_actionConnect_to_server_triggered()
**
** RETURNS:
**      void
**
** NOTES:
**  SLOT function. Catches when the user selects the "connect to server" menu item. Opens a dialog
** prompting the user for a display name, server host, and server port number to connect to. Starts
** the calls the client ConnectToServer function passing the port, host and a pointer to the GUI
**
******************************************************************************************************/
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

/*******************************************************************************************************
** Function: 	appendMessage(QString)
**
** DATE:		March 25, 2015
**
** DESIGNER:	Filip Gutica A00781910
**
** PROGRAMMER:	Filip Gutica A00781910
**
** INTERFACE:	appendMessage(QString)
**
** PARAMS:
**      str     - Message to be appended
**
** RETURNS:
**      void
**
** NOTES:
** Public function to append a new message to our text browser. Emites a signal telling our main
** thread that there is a new message to handle.
******************************************************************************************************/
void Application::appendMessage(QString str)
{
    emit valueChangedConvo(str);
}

/*******************************************************************************************************
** Function: 	addUser(QString)
**
** DATE:		March 25, 2015
**
** DESIGNER:	Filip Gutica A00781910
**
** PROGRAMMER:	Filip Gutica A00781910
**
** INTERFACE:	addUser(QString)
**
** PARAMS:
**      str     - User to be added to the list view
**
** RETURNS:
**      void
**
** NOTES:
** Public function to append a user to our list view. Emites a signal telling our main
** thread that a new user as connected.
******************************************************************************************************/
void Application::addUser(QString str)
{
    emit valueChangedUsr(str);
}

/*******************************************************************************************************
** Function: 	removeUser(QString)
**
** DATE:		March 25, 2015
**
** DESIGNER:	Filip Gutica A00781910
**
** PROGRAMMER:	Filip Gutica A00781910
**
** INTERFACE:	removeUser(QString)
**
** PARAMS:
**      str     - User to be removed from the list view
**
** RETURNS:
**      void
**
** NOTES:
** Public function to remove a user from our list view. Emites a signal telling our main
** thread that a user has left.
******************************************************************************************************/
void Application::removeUser(QString usr)
{
    emit valueUsrRemoved(usr);
}

/*******************************************************************************************************
** Function: 	addToList(QString)
**
** DATE:		March 25, 2015
**
** DESIGNER:	Filip Gutica A00781910
**
** PROGRAMMER:	Filip Gutica A00781910
**
** INTERFACE:	addToList(QString)
**
** PARAMS:
**      str     - User to be added to the list view
**
** RETURNS:
**      void
**
** NOTES:
** SLOT function catches the valueChangedUsr signal and adds the provided user to the listview
******************************************************************************************************/
void Application::addToList(QString str)
{
    if (!usrList.contains(str))
    {
        usrList.push_back(str);

        ui->listUsers->setModel(new QStringListModel(QList<QString>::fromVector(usrList)));
    }
}

/*******************************************************************************************************
** Function: 	removeFromList(QString)
**
** DATE:		March 25, 2015
**
** DESIGNER:	Filip Gutica A00781910
**
** PROGRAMMER:	Filip Gutica A00781910
**
** INTERFACE:	rempveFromList(QString)
**
** PARAMS:
**      usr     - User to be removed from the list view
**
** RETURNS:
**      void
**
** NOTES:
** SLOT function catches the valueChangedUsr signal and adds the provided user to the listview
******************************************************************************************************/
void Application::removeFromList(QString usr)
{
    if (usrList.contains(usr))
    {
        usrList.removeOne(usr);
    }

    ui->listUsers->setModel(new QStringListModel(QList<QString>::fromVector(usrList)));
}

/*******************************************************************************************************
** Function: 	on_btnSend_clicked()
**
** DATE:		March 25, 2015
**
** DESIGNER:	Filip Gutica A00781910
**
** PROGRAMMER:	Filip Gutica A00781910
**
** INTERFACE:	on_btnSend_clicked(QString)
**
** PARAMS:
**      usr     - User to be removed from the list view
**
** RETURNS:
**      void
**
** NOTES:
** SLOT function catches the valueChangedUsr signal and adds the provided user to the listview
******************************************************************************************************/
void Application::on_btnSend_clicked()
{
    QString text;

    text = QString("usr:%1:%2").arg(displayName).arg(ui->msgEdit->text());

    int size = text.size();

    appendMessage("Me: " + ui->msgEdit->text());

    SendMessage(text.toUtf8().constData(), size);

    ui->msgEdit->clear();
}

/*******************************************************************************************************
** Function: 	onReturnPressed()
**
** DATE:		March 25, 2015
**
** DESIGNER:	Filip Gutica A00781910
**
** PROGRAMMER:	Filip Gutica A00781910
**
** INTERFACE:	onReturnPressed()
**
** PARAMS:
**      usr     - User to be removed from the list view
**
** RETURNS:
**      void
**
** NOTES:
** SLOT function catches the valueChangedUsr signal and adds the provided user to the listview
******************************************************************************************************/
void Application::onReturnPressed()
{
    QString text;

    text = QString("usr:%1:%2").arg(displayName).arg(ui->msgEdit->text());

    int size = text.size();

    appendMessage("Me: " + ui->msgEdit->text());

    SendMessage(text.toUtf8().constData(), size);

    ui->msgEdit->clear();
}

/*******************************************************************************************************
** Function: 	on_action_save_convo_triggered()
**
** DATE:		March 25, 2015
**
** DESIGNER:	Auto Generated
**
** PROGRAMMER:	Filip Gutica A00781910
**
** INTERFACE:	on_action_save_convo_triggered()
**
** RETURNS:
**      void
**
** NOTES:
** SLOT function. Catches when the user selects the "Save Conversation" menu item.
** Creates a new file, writes out the conversation.
**
******************************************************************************************************/
void Application::on_action_save_convo_triggered()
{
    QDateTime local(QDateTime::currentDateTime());
    QString fname;
    fname = QString("Conversation: %1").arg(local.toString());

    qDebug() << fname;

    QFile file(fname);

    if (file.open(QIODevice::ReadWrite))
    {
        QString conversation = ui->txtConvo->toPlainText();
        file.write(conversation.toUtf8().constData(), conversation.size());
    }
}
