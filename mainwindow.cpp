#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "piremote/piremote.h"

 #include <QtWidgets>
#include <QtCore>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
    ui->setupUi(this);

    qmlView = new QQuickView();
        QWidget* container = QWidget::createWindowContainer(qmlView, ui->mainFrame);
        qmlView->setSource(QUrl("qrc:///qml/mainWindow.qml"));

    QHBoxLayout *l = new QHBoxLayout(ui->mainFrame);
        l->addWidget(container);
        ui->mainFrame->setLayout(l);

    connect(ui->volume, SIGNAL(valueChanged(int)), this, SLOT(setGeneralVolume(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setGeneralVolume(int v)
{
    PIR->triggerApp("screen", "volume", QString().setNum(v));
}

void MainWindow::toggleShow()
{
    if(isVisible())
        hide();
    else if(PIR->interface()->isRemoteConnected())
        show();
}
