#ifndef REMOTECONTROLINTERFACE_H
#define REMOTECONTROLINTERFACE_H

#include <QtNetwork>
#include <QObject>
#include <QtQuick>
#include "remoteapp.h"

#define PIR PIRemote::remote()

#define CHAR 0x00
#define STRING 0x01
#define APPS 0xC9
#define APPS_SYNC 0xC8
#define MODELS 0x65
#define MODELS_SYNC 0x64

class RemoteControlInterface;

class PIRemote: public QObject{
    Q_OBJECT
public:
    static PIRemote* remote(){return piRemote;}
    static void initRemote(QQmlApplicationEngine* engine = NULL){piRemote = new PIRemote(engine);}

    RemoteControlInterface* interface(){return _interface;}

public slots:

    void dataReceived(quint8 dataType, QByteArray data);
    void initConnection();

    void triggerApp(quint8 appID, quint8 actionID, QString args="");
    bool triggerApp(QString appName, QString action, QString args="");


protected:
    PIRemote(QQmlApplicationEngine* engine=NULL);
    static PIRemote* piRemote;

    RemoteControlInterface* _interface;
    QQmlApplicationEngine* engine;

    void generateApps(QString appData);
    QList<RemoteApp*> apps;
};

class RemoteControlInterface: public QObject
{
    Q_OBJECT

public:
    RemoteControlInterface(QObject *parent);
    ~RemoteControlInterface();

    bool isRemoteConnected(){return isConnected;}
signals:
    void connected();
    void disconnected();

    void receivedChar(const char* data);
    void receivedString(QString message);

public slots:
    void connectRemote(QString address, QString port, QString name);
    void connectRemote(QString address, quint16 port, QString name);

    void disconnectRemote();


    void send(QString instruction);
    void send(quint8 dataType, QByteArray data);

    void read();


    void initConnexion();
    void onConnexionLost();

protected slots:
    void connexionTimeout();

private:
    void write(QByteArray data);


    quint16 blockSize;

    QTcpSocket* socket;
    QTimer connexionTimer;
    QString name="";
    bool isConnected=false;
};

#endif // REMOTECONTROLINTERFACE_H
