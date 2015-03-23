/********************************************************************************
** Form generated from reading UI file 'application.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_APPLICATION_H
#define UI_APPLICATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Application
{
public:
    QAction *actionConnect_to_server;
    QWidget *centralWidget;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QLineEdit *msgEdit;
    QListView *clientList;
    QPushButton *btnSend;
    QTextBrowser *txtConvo;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Application)
    {
        if (Application->objectName().isEmpty())
            Application->setObjectName(QStringLiteral("Application"));
        Application->resize(845, 472);
        actionConnect_to_server = new QAction(Application);
        actionConnect_to_server->setObjectName(QStringLiteral("actionConnect_to_server"));
        centralWidget = new QWidget(Application);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout_2 = new QGridLayout(centralWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        msgEdit = new QLineEdit(centralWidget);
        msgEdit->setObjectName(QStringLiteral("msgEdit"));

        gridLayout->addWidget(msgEdit, 1, 1, 1, 1);

        clientList = new QListView(centralWidget);
        clientList->setObjectName(QStringLiteral("clientList"));
        clientList->setMaximumSize(QSize(250, 16777215));

        gridLayout->addWidget(clientList, 0, 0, 1, 1);

        btnSend = new QPushButton(centralWidget);
        btnSend->setObjectName(QStringLiteral("btnSend"));

        gridLayout->addWidget(btnSend, 1, 2, 1, 1);

        txtConvo = new QTextBrowser(centralWidget);
        txtConvo->setObjectName(QStringLiteral("txtConvo"));

        gridLayout->addWidget(txtConvo, 0, 1, 1, 2);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);

        Application->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Application);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 845, 30));
        Application->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Application);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        Application->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(Application);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        Application->setStatusBar(statusBar);

        mainToolBar->addAction(actionConnect_to_server);

        retranslateUi(Application);

        QMetaObject::connectSlotsByName(Application);
    } // setupUi

    void retranslateUi(QMainWindow *Application)
    {
        Application->setWindowTitle(QApplication::translate("Application", "Application", 0));
        actionConnect_to_server->setText(QApplication::translate("Application", "Connect to server", 0));
        btnSend->setText(QApplication::translate("Application", "Send", 0));
    } // retranslateUi

};

namespace Ui {
    class Application: public Ui_Application {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_APPLICATION_H
