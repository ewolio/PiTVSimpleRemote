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

    // QWidget interface
protected:
    void mouseMoveEvent(QMouseEvent *);

    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *);

    // QWidget interface
protected:
    void dragEnterEvent(QDragEnterEvent *);
    void dragMoveEvent(QDragMoveEvent *);
};

#endif // MAINWINDOW_H
