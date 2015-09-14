#ifndef REMOTEAPP_H
#define REMOTEAPP_H

#include <QObject>

class RemoteAppAction;

class RemoteApp : public QObject
{
    Q_OBJECT
public:
    explicit RemoteApp(QString name, quint8 appID, QObject *parent = 0);

    QString name() const {return _name;}
    quint8 appID() const {return _appID;}
    quint8 actionIDByName(QString name);

    void readReply(QString reply);

    static RemoteApp *fromString(QString structure, QObject *parent=0);

signals:
    void replyReceived(QString reply);

public slots:
    bool trigger(QString action, QString args="");
    void acceptReply();


protected:
    void add(RemoteAppAction* action);

private:
    const QString _name;
    const quint8 _appID;

    QList<RemoteAppAction*> actions;
};

class RemoteAppAction: public QObject{
    Q_OBJECT
public:
    explicit RemoteAppAction(QString name, quint8 actionID, RemoteApp *app);

    QString getName() const {return _name;}
    quint8 getActionID() const {return _code;}

private:
    const QString _name;
    const quint8 _code;
    const RemoteApp* _app;
};

#endif // REMOTEAPP_H
