#include "configdialog.h"
#include "ui_configdialog.h"

ConfigDialog::ConfigDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigDialog)
{
    ui->setupUi(this);

    connect(ui->connectButton, SIGNAL(clicked(bool)), this, SLOT(connectButtonClicked()));

    ui->connectButton->setText("Connect");

    t = new QTimer();
    t->setInterval(3000);
    connect(t, SIGNAL(timeout()), this, SLOT(connectButtonClicked()));
    t->start();

    autoConnect = true;
}

ConfigDialog::~ConfigDialog()
{
    delete ui;
}

void ConfigDialog::remoteConnected()
{
    ui->connectButton->setEnabled(true);
    ui->connectButton->setText("Disconnect");
    t->stop();
}

void ConfigDialog::remoteDisconnected()
{
    ui->connectButton->setText("Connect");
    ui->serverAddress->setEnabled(true);
    ui->serverPort->setEnabled(true);
    ui->remoteName->setEnabled(true);
    ui->connectButton->setEnabled(true);

    if(!isVisible()&&autoConnect)
        t->start();
}

void ConfigDialog::connectButtonClicked()
{
    if(ui->connectButton->text().remove('&')=="Connect"){
        ui->serverAddress->setEnabled(false);
        ui->serverPort->setEnabled(false);
        ui->remoteName->setEnabled(false);
        ui->connectButton->setEnabled(false);
        ui->connectButton->setText("Connecting");
        emit connectRemote(ui->serverAddress->text(), ui->serverPort->value(), ui->remoteName->text());
        autoConnect= true;
    }else if(ui->connectButton->text().remove('&') == "Disconnect"){
        emit disconnectRemote();
        autoConnect = false;
    }
}

void ConfigDialog::closeEvent(QCloseEvent *)
{
    if(ui->connectButton->text()!="Disconnect"&&autoConnect)
        t->start();
}

void ConfigDialog::showEvent(QShowEvent *)
{
    t->stop();
}
