#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFrame>

class DropArea;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void setGeneralVolume(int v);
    void toggleShow();

private:
    Ui::MainWindow *ui;
    DropArea* area;
};

class DropArea: public QFrame{
    Q_OBJECT
public:
    explicit DropArea();




    // QWidget interface
protected:
    void dropEvent(QDropEvent *e);
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void dragEnterEvent(QDragEnterEvent *);
    void dragMoveEvent(QDragMoveEvent *);
};

#endif // MAINWINDOW_H
