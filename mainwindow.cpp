#include "mainwindow.h"
#include "ui_mainwindow.h"

 #include <QtWidgets>
#include <QtCore>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setAcceptDrops(true);
    area = new DropArea();
    ui->centralLayout->addWidget(area);
}

MainWindow::~MainWindow()
{
    delete ui;
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

        grabMouse();
}

void DropArea::dropEvent(QDropEvent *e)
{
    e->accept();
    e->acceptProposedAction();
    if(e->mimeData()->hasUrls())
        qWarning()<<e->mimeData()->urls();
    if(e->mimeData()->hasText())
        qWarning()<<e->mimeData()->text();
}


void DropArea::mouseMoveEvent(QMouseEvent *e)
{
    e->accept();
    qWarning()<<"move!!!!!";
}

void DropArea::mousePressEvent(QMouseEvent *e)
{
    e->accept();
    qWarning()<<"click";
}

void DropArea::dragEnterEvent(QDragEnterEvent *e)
{
    e->acceptProposedAction();
}

void DropArea::dragMoveEvent(QDragMoveEvent *e)
{
    e->acceptProposedAction();
}
