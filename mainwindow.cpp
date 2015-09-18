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
    setAcceptDrops(true);
    area = new DropArea();
    ui->centralLayout->addWidget(area);

//    ui->volume->setRange(-6,3);
//    ui->volume->setTickInterval(1);
//    ui->volume->setTickPosition(QSlider::TicksLeft);
//    ui->volume->setSingleStep(1);
//    ui->volume->setValue(-1);
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

DropArea::DropArea(): QFrame()
{
    setLineWidth(5);
    setMidLineWidth(3);
    setAcceptDrops(true);

    setFrameShadow(QFrame::Raised);

    QHBoxLayout *layout = new QHBoxLayout(this);
        QLabel* text = new QLabel("Droppez ici!");
        text->setAlignment(Qt::AlignHCenter);
        layout->addWidget(text);
}

void DropArea::dropEvent(QDropEvent *e)
{
    e->accept();
    e->acceptProposedAction();
    if(e->mimeData()->hasText()){
        qWarning()<<e->mimeData()->text();
        PIR->triggerApp("screen", "window", "0|stream:"+e->mimeData()->text());
        PIR->triggerApp("screen", "window", "0|play");
    }
}


void DropArea::mouseMoveEvent(QMouseEvent *e)
{
    e->accept();
}

void DropArea::mousePressEvent(QMouseEvent *e)
{
    e->accept();
    PIR->triggerApp("screen","window", "0|togglePause");
}

void DropArea::dragEnterEvent(QDragEnterEvent *e)
{
    e->acceptProposedAction();
}

void DropArea::dragMoveEvent(QDragMoveEvent *e)
{
    e->acceptProposedAction();
}
