#-------------------------------------------------
#
# Project created by QtCreator 2015-03-23T10:09:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ChatClient
TEMPLATE = app


SOURCES += main.cpp\
        application.cpp \
    client.cpp \
    dialog.cpp

HEADERS  += application.h \
    client.h \
    dialog.h

FORMS    += application.ui \
    dialog.ui
