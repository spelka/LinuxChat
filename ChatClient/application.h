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
    void removeUser(QString);

private slots:
    void on_actionConnect_to_server_triggered();
    void addToList(QString);
    void removeFromList(QString);
    void on_btnSend_clicked();

private:
    Ui::Application *ui;
    QVector<QString> usrList;
    QString displayName;


signals:
    void valueChangedConvo(QString);
    void valueChangedUsr(QString);
    void valueUsrRemoved(QString);
};

#endif // APPLICATION_H
