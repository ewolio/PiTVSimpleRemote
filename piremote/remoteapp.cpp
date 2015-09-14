#include "remoteapp.h"
#include "piremote.h"

RemoteApp::RemoteApp(QString name, quint8 appID, QObject *parent): QObject(parent), _name(name), _appID(appID)
{

}

quint8 RemoteApp::actionIDByName(QString name)
{
    RemoteAppAction* action = NULL;
    for (int i = 0; i < actions.size(); ++i) {
        if(actions.at(i)->getName() == name)
            action = actions.at(i);
    }
    if(action==NULL)
        return 255;
    return action->getActionID();
}

void RemoteApp::add(RemoteAppAction *action)
{
    actions.append(action);
}

RemoteApp* RemoteApp::fromString(QString structure, QObject* parent)
{
    QStringList info = structure.split("|");

    QStringList d = info.at(0).split(":");
    RemoteApp* app = new RemoteApp(d.last(), (quint8) d.first().toInt(), parent);

    for (int i = 1; i < info.size(); ++i) {
        d = info.at(i).split(":");
        app->add(new RemoteAppAction(d.last(), (quint8) d.first().toInt(), app));
    }

    return app;
}


bool RemoteApp::trigger(QString action, QString args){
    quint8 actionID = actionIDByName(action);

    if(actionID==255)
        return false;

    PIR->triggerApp(_appID, actionID, args);
    return true;
}

void RemoteApp::acceptReply()
{
    PIR->triggerApp(_appID, 0xFF);
}


void RemoteApp::readReply(QString reply)
{
    emit replyReceived(reply);
}

/************************************************************
 *                  RemoteAppAction
 * *********************************************************/


RemoteAppAction::RemoteAppAction(QString name, quint8 actionID, RemoteApp *app): QObject(app), _name(name), _code(actionID)
{
    _app = app;
}
