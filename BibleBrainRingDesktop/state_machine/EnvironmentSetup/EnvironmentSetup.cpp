#include "EnvironmentSetup.hpp"

EnvironmentSetup::EnvironmentSetup(QObject *parent)
    : StateAbstract(__FUNCTION__, parent)
{
    providerQml->setCurrentAppState(BibleBrainRing::EnvironmentSetup);
}

StateAbstract* EnvironmentSetup::onQmlButtonClicked(const BibleBrainRing::Button button)
{
    if (button == BibleBrainRing::ButtonComeback) {
        return new StartStateMenuMain();
    }
    else if (button == BibleBrainRing::ButtonNext) {
        return new RegistrationStateMain();
    }
    return nullptr;
}
