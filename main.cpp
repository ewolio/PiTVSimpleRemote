#include "mainwindow.h"
#include <QApplication>
#include <QSystemTrayIcon>
#include <QIcon>
#include <QObject>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    QSystemTrayIcon* icon = new QSystemTrayIcon(&w);
    icon->setIcon(QIcon("../../images/trayIcon.svg"));
    icon->show();
    w.connect(icon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), &w, SLOT(show()));


    return a.exec();
}
