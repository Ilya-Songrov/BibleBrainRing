#include "biblebrainringapplicationengine.h"

BibleBrainRingApplicationEngine::BibleBrainRingApplicationEngine(QObject *parent)
    : QQmlApplicationEngine(parent)
    , currentState(nullptr)
{
    createUtils();
    setConnections();
    currentState = new InitStateMain(this);
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


