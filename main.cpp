#include "mainwindow.h"
#include <QApplication>
#include <QSystemTrayIcon>
#include <QIcon>
#include "piremote/piremote.h"
#include <QObject>
#include <QMenu>
#include "configdialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;

    QPixmap icon(":/img/trayIcon");
    QPixmap iconGrayScale(":/img/trayIconDisconnected");
    w.setWindowIcon(icon);

    PIRemote::initRemote();

    ConfigDialog d;
    d.connect(&d, SIGNAL(connectRemote(QString,quint16,QString)), PIR->interface(), SLOT(connectRemote(QString,quint16,QString)));
    d.connect(&d, SIGNAL(disconnectRemote()), PIR->interface(), SLOT(disconnectRemote()));
    d.connect(PIR->interface(), SIGNAL(disconnected()), &d, SLOT(remoteDisconnected()));
    d.connect(PIR->interface(), SIGNAL(connected()), &d, SLOT(remoteConnected()));




    d.setWindowIcon(iconGrayScale);

    QSystemTrayIcon* systemBarIcon = new QSystemTrayIcon(iconGrayScale);

    d.connect(PIR->interface(), &RemoteControlInterface::connected, [icon, systemBarIcon](){systemBarIcon->setIcon(icon);});
    d.connect(PIR->interface(), &RemoteControlInterface::disconnected, [iconGrayScale, systemBarIcon](){systemBarIcon->setIcon(iconGrayScale);});
//    d.connect(PIR->interface(), &RemoteControlInterface::connected, [icon, &d](){d->setWindowIcon(icon);});
//    d.connect(PIR->interface(), &RemoteControlInterface::disconnected, [iconGrayScale, &d](){d->setWindowIcon(iconGrayScale);});
    d.connect(systemBarIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), &d, SLOT(systemTrayClicked()));


    QMenu* m = new QMenu(&d);
        m->addAction("Configuration", &d, SLOT(show()));

    systemBarIcon->setContextMenu(m);

    systemBarIcon->show();
    w.connect(systemBarIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), &w, SLOT(toggleShow()));
    w.connect(PIR->interface(), SIGNAL(disconnected()), &w, SLOT(close()));



    return a.exec();
}
