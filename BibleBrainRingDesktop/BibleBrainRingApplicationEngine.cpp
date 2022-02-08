#include "BibleBrainRingApplicationEngine.h"

BibleBrainRingApplicationEngine::BibleBrainRingApplicationEngine(QObject *parent)
    : QQmlApplicationEngine(parent)
    , currentState(nullptr)
{
    createUtils();
    setConnections();
#ifdef QT_DEBUG
    currentState = new InitStateMain(this);
//    currentState = new RegistrationStateMain();;
    currentState = new GameSession();;
#else
    currentState = new InitStateMain(this);
#endif
}

BibleBrainRingApplicationEngine::~BibleBrainRingApplicationEngine()
{

}

void BibleBrainRingApplicationEngine::onEndQmlCreation()
{
    StateAbstract* state = currentState->onEndQmlCreation();
    changeAppState(state);
}

void BibleBrainRingApplicationEngine::onQmlButtonClicked(const BibleBrainRing::Button button)
{
    StateAbstract* state = currentState->onQmlButtonClicked(button);
    changeAppState(state);
}

void BibleBrainRingApplicationEngine::changeAppState(StateAbstract* state)
{
    if (state) {
        delete currentState;
        currentState = state;
    }
}

void BibleBrainRingApplicationEngine::setConnections()
{
    connect(providerQml.get(), &ProviderQml::onEndQmlCreation   , this, &BibleBrainRingApplicationEngine::onEndQmlCreation);
    connect(providerQml.get(), &ProviderQml::onQmlButtonClicked , this, &BibleBrainRingApplicationEngine::onQmlButtonClicked);
}


