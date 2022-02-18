#include "EnvironmentSetup.hpp"
#include "all_states.h"

EnvironmentSetup::EnvironmentSetup(const QString& objectName, QObject *parent)
    : StateAbstract(objectName, parent)
{
    providerQml->setCurrentAppState(BibleBrainRing::EnvironmentSetup);

#ifdef QT_DEBUG

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
    else if (button == BibleBrainRing::ButtonAddBulb) {
        addBulb();
    }
    return nullptr;
}


QString EnvironmentSetup::getListNetwork()
{
    QString res;
    const auto list = QNetworkInterface::allAddresses();
    for (const QHostAddress& hostAddress: list) {
        res += hostAddress.toString() + "\n";
    }
    return res;
}

void EnvironmentSetup::addBulb()
{
    const QString networksStr = "Write bulb host and port like this:\n 192.168.0.104:55443. \n\n\nAvailable network list:\n" + getListNetwork();
    const QString hostPort = QInputDialog::getText(nullptr, "Custom bulb", networksStr);
    const auto list = hostPort.split(":");
    if (list.size() == 2) {
        YeelightBulb::Bulb* bulb = new YeelightBulb::Bulb(bibleBrainRingServerClassical.get());
        const bool ret = bulb->connectToBulb(QHostAddress(list.front()), list.back().toUShort());
        const QString address = "Your bulb address: " + bulb->getPeerHostPort();
        const QString message = ret ? address : "I can't connect to bulb";
        QMessageBox::information(nullptr, "Bulb info", message);
        if (ret) {
            vecBulbs.append(bulb);
        }
    }
    else{
        emit providerQml->showMessage("Parse error!");
    }
}
