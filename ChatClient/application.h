#ifndef APPLICATION_H
#define APPLICATION_H

#include <QMainWindow>
#include <QStringListModel>
#include <QVector>
#include "client.h"
#include "dialog.h"

namespace Ui {
class Application;
}

class Application : public QMainWindow
{
    Q_OBJECT

public:
    explicit Application(QWidget *parent = 0);
    ~Application();
    void appendMessage(QString str);
    void addUser(QString str);
    void removeUser(int);

private slots:
    void on_actionConnect_to_server_triggered();
    void addToList(QString);
    void removeFromList(int);

    void on_btnSend_clicked();

private:
    Ui::Application *ui;
    QVector<QString> usrList;


signals:
    void valueChangedConvo(QString);
    void valueChangedUsr(QString);
    void valueUsrRemoved(int);
};

#endif // APPLICATION_H
