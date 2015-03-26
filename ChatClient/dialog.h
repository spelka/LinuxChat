/*****************************************************************************************************
**	SOURCE FILE:	dialog.h 			header file for dialog.cpp
**
**	PROGRAM:	ChatClient

**
**	DATE: 		March 25, 2015
**
**
**	DESIGNER: 	Filip Gutica A00781910
**
**	PROGRAMMER: Filip Gutica A00781910
**
*********************************************************************************************************/
#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    QString getPort();
    QString getHost();
    QString getDisplayName();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
