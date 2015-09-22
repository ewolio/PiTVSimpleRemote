#-------------------------------------------------
#
# Project created by QtCreator 2015-09-13T02:29:13
#
#-------------------------------------------------

QT       += core gui network quick

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PiTVSimpleRemote
TEMPLATE = app
CONFIG += c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    piremote/piremote.cpp \
    piremote/remoteapp.cpp \
    configdialog.cpp

HEADERS  += mainwindow.h \
    piremote/piremote.h \
    piremote/remoteapp.h \
    configdialog.h

FORMS    += mainwindow.ui \
    configdialog.ui

DISTFILES += \
    mainWindow.qml

RESOURCES = ressources.qrc
