/*****************************************************************************************************
**	SOURCE FILE:	dialog.cpp 			UI Class for our dialog.
**
**	PROGRAM:	ChatClient
**
**  CONSTRUCTOR:
**      Dialog(QWidget*)
**
**  DESTRUCTOR:
**      ~Dialog()
**
**	FUNCTIONS:
**		QString getPort()
**		QString getHost()
**		QString getDisplayName()
**
**	DATE: 		March 25, 2015
**
**
**	DESIGNER: 	Filip Gutica A00781910
**
**	PROGRAMMER: Filip Gutica A00781910
**
*********************************************************************************************************/
#include "dialog.h"
#include "ui_dialog.h"

/*******************************************************************************************************
** Function: 	Dialog
**
** DATE:		March 25, 2015
**
** DESIGNER:	Auto Generated
**
** PROGRAMMER:	Auto Generated && Filip Gutica A00781910
**
** INTERFACE:	Dialog(QWidget)
**
**
** NOTES:
** Constructor for our Dialog GUI. Constructs the ui, initializes UI objects for this dialog.
******************************************************************************************************/
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    ui->displayNameEdit->setFocus();
}

/*******************************************************************************************************
** Function: 	~Dialog
**
** DATE:		March 25, 2015
**
** DESIGNER:	Auto Generated
**
** PROGRAMMER:	Autp Generated
**
** INTERFACE:	~Dialog()
**
**
** NOTES:
** Destructor for our Dialog GUI. Cleans up the ui, deletes UI objects.
******************************************************************************************************/
Dialog::~Dialog()
{
    delete ui;
}


/*******************************************************************************************************
** Function: 	getPort()
**
** DATE:		March 25, 2015
**
** DESIGNER:	Filip Gutica A00781910
**
** PROGRAMMER:	Filip Gutica A00781910
**
** INTERFACE:	getPort()
**
** RETURNS:
**      QString     - Port number entered by the user
**
** NOTES:
** returns the contents of the port lineEdit.
******************************************************************************************************/
QString Dialog::getPort()
{
    return ui->portEdit->text();
}

/*******************************************************************************************************
** Function: 	getHost()
**
** DATE:		March 25, 2015
**
** DESIGNER:	Filip Gutica A00781910
**
** PROGRAMMER:	Filip Gutica A00781910
**
** INTERFACE:	getHost()
**
** RETURNS:
**      QString     - IP entered by the user
**
** NOTES:
** returns the contents of the host lineEdit.
******************************************************************************************************/
QString Dialog::getHost()
{
    return ui->hostEdit->text();
}

/*******************************************************************************************************
** Function: 	getDisplayName()
**
** DATE:		March 25, 2015
**
** DESIGNER:	Filip Gutica A00781910
**
** PROGRAMMER:	Filip Gutica A00781910
**
** INTERFACE:	getDisplayName()
**
** RETURNS:
**      QString     - display name entered by the user
**
** NOTES:
** returns the contents of the display name lineEdit.
******************************************************************************************************/
QString Dialog::getDisplayName()
{
    return ui->displayNameEdit->text();
}
