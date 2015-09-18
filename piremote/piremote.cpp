#include "piremote.h"

PIRemote* PIRemote::piRemote = NULL;

PIRemote::PIRemote(QQmlApplicationEngine* engine): QObject(){
    _interface = new RemoteControlInterface(this);
    this->engine = engine;
}

void PIRemote::dataReceived(quint8 dataType, QByteArray data)
{
    qWarning()<<"Received: "<<dataType<<"|"<<data;

    switch(dataType){
        case CHAR:         //char*
            qWarning()<<data;
            break;
        case STRING:         //QString utf8
            qWarning()<<QString::fromUtf8(data);
            break;
    }

    if(dataType >= APPS_SYNC){
        //Apps
        if(dataType==APPS_SYNC){
            generateApps(QString::fromUtf8(data));
        }else{
            quint8 appID = dataType - APPS;
            apps.at(appID)->readReply(QString::fromUtf8(data));
        }

    }else if(dataType>=MODELS_SYNC){
        //Model modif

    }
}

void PIRemote::initConnection()
{
    //Ask for apps tree
    _interface->send(APPS_SYNC, "i");

}

//------------  App control    -------------------
void PIRemote::triggerApp(quint8 appID, quint8 actionID, QString args)
{
    _interface->send(APPS+appID, actionID + args.toUtf8());
}

bool PIRemote::triggerApp(QString appName, QString action, QString args)
{
    RemoteApp* app = NULL;

    for (int i = 0; i < apps.size(); ++i) {
        if(apps.at(i)->name() == appName)
                app = apps.at(i);
    }

    if(app == NULL)
        return false;

    quint8 actionID = app->actionIDByName(action);
    if(actionID == 255)
        return false;

    triggerApp(app->appID(), actionID, args);
    return true;
}

void PIRemote::generateApps(QString appData)
{
    QStringList info = appData.split("\n", QString::SkipEmptyParts);

    for (int i = 0; i < info.size(); ++i){
        apps.append(RemoteApp::fromString(info.at(i)));
        if(engine != NULL)
            engine->rootContext()->setContextProperty(apps.last()->name(), apps.last());
    }

}






/***************************************************
 *              RemoteControlInterface
 * ************************************************/


RemoteControlInterface::RemoteControlInterface(QObject* parent): QObject(parent)
{
    socket = new QTcpSocket(this);
    connect(socket, SIGNAL(connected()), this, SLOT(initConnexion()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(onConnexionLost()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(read()));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SIGNAL(disconnected()));

    blockSize = 0;
}

RemoteControlInterface::~RemoteControlInterface()
{
    socket->disconnect();
    delete socket;
}



void RemoteControlInterface::connectRemote(QString address, QString port, QString name)
{
    bool ok = false;
    quint16 portInt = port.trimmed().toInt(&ok);

    if(ok)
        connectRemote(address.trimmed(), portInt, name);
    else
        emit(disconnected());
}

void RemoteControlInterface::connectRemote(QString address, quint16 port, QString name)
{
    socket->connectToHost(address, port);
    qWarning()<<"Connecting to: "<<address<<":"<<port<<" as "<<name;
    connexionTimer.singleShot(10000, this, SLOT(connexionTimeout()));
    this->name = name;
}

void RemoteControlInterface::disconnectRemote()
{
    socket->disconnectFromHost();
}

void RemoteControlInterface::send(QString instruction)
{
    send(STRING, instruction.toUtf8());

}

void RemoteControlInterface::send(quint8 dataType, QByteArray data)
{
    qWarning()<<"Sending: "<<dataType<<"|"<<data;
    write(dataType + data);
}



void RemoteControlInterface::read()
{

    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_4_0);

    if (blockSize == 0) {
        if (socket->bytesAvailable() < (int)sizeof(quint16))
            return;

        in >> blockSize;
    }

    if (socket->bytesAvailable() < blockSize)
        return;

    QByteArray data;
    in >> data;

    if(isConnected){

        quint16 dataType = data.at(0);
        data = data.right(data.size()-1);

        PIR->dataReceived(dataType, data);

    }else{
        if(data.startsWith("PI")){
            isConnected = true;
            emit connected();
            PIR->initConnection();
        }
    }

    blockSize = 0;
}



void RemoteControlInterface::initConnexion()
{
    isConnected = false;
    write('P'+name.toUtf8());
}

void RemoteControlInterface::onConnexionLost()
{
    isConnected = false;
    emit(disconnected());
}

void RemoteControlInterface::connexionTimeout()
{
    if(!isConnected)
        disconnectRemote();
}

void RemoteControlInterface::write(QByteArray data)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);

    out<<(quint16)data.size();
    out<<data;

    socket->write(block);
}


