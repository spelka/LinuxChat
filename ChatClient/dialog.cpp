#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    ui->displayNameEdit->setFocus();
}

Dialog::~Dialog()
{
    delete ui;
}

QString Dialog::getPort()
{
    return ui->portEdit->text();
}

QString Dialog::getHost()
{
    return ui->hostEdit->text();
}

QString Dialog::getDisplayName()
{
    return ui->displayNameEdit->text();
}
