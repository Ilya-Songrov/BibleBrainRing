#include "EnvironmentSetup.hpp"

EnvironmentSetup::EnvironmentSetup(QObject *parent)
    : StateAbstract(__FUNCTION__, parent)
{
    providerQml->setCurrentAppState(BibleBrainRing::EnvironmentSetup);

#ifdef QT_DEBUG
    vecBulbs.append(new YeelightBulb::Bulb(providerQml.get()));
    vecBulbs.append(new YeelightBulb::Bulb(providerQml.get()));
    vecBulbs[0]->connectToBulb(QHostAddress("192.168.0.107"), 55443);
//    vecBulbs[0]->connectToBulb(QHostAddress("192.168.0.107"), 55443);
    for (YeelightBulb::Bulb* bulb: qAsConst(vecBulbs)) {
        bulb->set_power(false, YeelightBulb::Bulb::Sudden, 1);
    }
#endif
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
