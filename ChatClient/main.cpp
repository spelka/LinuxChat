/*****************************************************************************************************
**	SOURCE FILE:	main.cpp
**
**	PROGRAM:	ChatClient

**	FUNCTIONS:
**		int main(argc, char* argv[])
**
**	DATE: 		March 25, 2015
**
**
**	DESIGNER: 	Auto generated file
**
**	PROGRAMMER: Auto generated file
**
*********************************************************************************************************/
#include "application.h"
#include <QApplication>

/*******************************************************************************************************
** Function: 	main
**
** DATE:		March 25, 2015
**
** DESIGNER:	Auto Generated
**
** PROGRAMMER:	Auto Generated
**
** INTERFACE:	Application(QWidget)
**
**
** NOTES:
** Main entry point for our program.
******************************************************************************************************/
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Application w;
    w.show();

    return a.exec();
}
