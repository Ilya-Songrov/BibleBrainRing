#include "EnvironmentSetup.hpp"

EnvironmentSetup::EnvironmentSetup(QObject *parent)
    : StateAbstract(__FUNCTION__, parent)
{
    providerQml->setCurrentAppState(BibleBrainRing::EnvironmentSetup);
}

StateAbstract* EnvironmentSetup::onQmlButtonClicked(const BibleBrainRing::Button button)
{
    if (button == BibleBrainRing::ButtonComeback) {
        const int res = QMessageBox::question(nullptr, QObject::tr("Game"), "Do you want to end the game and lose all progress?");
        if (res == QMessageBox::Button::Yes) {
            return new StartStateMenuMain();
        }
    }
    else if (button == BibleBrainRing::ButtonNext) {
        return new RegistrationStateMain();
    }
    return nullptr;
}
