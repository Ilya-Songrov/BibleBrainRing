#include "biblebrainringapplicationengine.h"

BibleBrainRingApplicationEngine::BibleBrainRingApplicationEngine(QObject *parent) : QQmlApplicationEngine(parent)
  #ifdef QT_DEBUG
  , bbrClassical(new BibleBrainRingServerClassical(new TcpServer("127.0.0.1", "9090", this)))
  #endif
{
    const bool ret = bbrClassical->initServer();
    if (!ret) {
        qWarning() << "Error server init" << Qt::endl;
        return;
    }
    bbrClassical->onConnectNewTeam([](const TeamDto& team){ qDebug() << "new team:" << team.guid << Qt::endl; });
    bbrClassical->onTeamDtoChanged([](const TeamDto& team){ qDebug() << "new team data:" << team.status << Qt::endl; });
    bbrClassical->startRegistration();
}

BibleBrainRingApplicationEngine::~BibleBrainRingApplicationEngine()
{

}


