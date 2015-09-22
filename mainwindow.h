#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QQuickView>
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
    QQuickView* qmlView;
};
#endif // MAINWINDOW_H
