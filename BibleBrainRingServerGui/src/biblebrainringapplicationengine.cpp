#include "biblebrainringapplicationengine.h"

BibleBrainRingApplicationEngine::BibleBrainRingApplicationEngine(QObject *parent) : QQmlApplicationEngine(parent)
  , currentState(nullptr)
{
    createUtils();
    setConnections();
    changeCurrentState(new InitStateMain(this));

    //    TcpServer tcpServer("127.0.0.1", "9090");
    //    BibleBrainRingServerClassical bibleBrainRingServerClassical(&tcpServer);
    //    const bool ret = bibleBrainRingServerClassical.initServer();
    //    if (!ret) {
    //        qWarning() << "Error server init" << Qt::endl;
    //        return 1;
    //    }
    //    bibleBrainRingServerClassical.startRegistration();
    //    bibleBrainRingServerClassical.onConnectNewTeam([](const TeamDto& team){ qDebug() << "new team:" << team.guid << Qt::endl; });
    //    bibleBrainRingServerClassical.onTeamDtoChanged([](const TeamDto& team){ qDebug() << "new team data:" << team.status << Qt::endl; });
}

BibleBrainRingApplicationEngine::~BibleBrainRingApplicationEngine()
{
    delete currentState;
}

void BibleBrainRingApplicationEngine::onEndQmlCreation()
{
    StateAbstract *state = currentState->onEndQmlCreation();
    changeCurrentState(state);
}

void BibleBrainRingApplicationEngine::onQmlButtonClicked(const BibleBrainRing::Button button)
{
    qDebug() << "Button was clicked:" << button << Qt::endl;
    StateAbstract *state = currentState->onQmlButtonClicked(button);
    changeCurrentState(state);
}

void BibleBrainRingApplicationEngine::setConnections()
{
    connect(providerQml.get(), &ProviderQml::onEndQmlCreation, this, &BibleBrainRingApplicationEngine::onEndQmlCreation);
    connect(providerQml.get(), &ProviderQml::onQmlButtonClicked, this, &BibleBrainRingApplicationEngine::onQmlButtonClicked);
}

void BibleBrainRingApplicationEngine::changeCurrentState(StateAbstract *state)
{
    if (state) {
        delete currentState;
        currentState = state;
    }
}

