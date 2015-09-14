#-------------------------------------------------
#
# Project created by QtCreator 2015-09-13T02:29:13
#
#-------------------------------------------------

QT       += core gui network quick

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PiTVSimpleRemote
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    piremote/piremote.cpp \
    piremote/remoteapp.cpp

HEADERS  += mainwindow.h \
    piremote/piremote.h \
    piremote/remoteapp.h

FORMS    += mainwindow.ui
