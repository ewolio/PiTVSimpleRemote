#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H

#include <QDialog>
#include <QTimer>
#include <qdebug.h>

namespace Ui {
class ConfigDialog;
}

class ConfigDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConfigDialog(QWidget *parent = 0);
    ~ConfigDialog();

public slots:
    void remoteConnected();
    void remoteDisconnected();

    void connectButtonClicked();
signals:
    void connectRemote(QString hostname, quint16 port, QString name);
    void disconnectRemote();

protected:


private:
    Ui::ConfigDialog *ui;
    QTimer *t;
    bool autoConnect;

protected:
    void closeEvent(QCloseEvent *);
    void showEvent(QShowEvent *);
};

#endif // CONFIGDIALOG_H
