#include "EnvironmentSetupHttpServer.hpp"

EnvironmentSetupHttpServer::EnvironmentSetupHttpServer(QObject *parent)
    : EnvironmentSetup(__FUNCTION__, parent)
{

#ifdef QT_DEBUG
//    vecBulbs.append(new YeelightBulb::Bulb(providerQml.get()));
////    vecBulbs.append(new YeelightBulb::Bulb(providerQml.get()));
//    vecBulbs[0]->connectToBulb(QHostAddress("192.168.0.110"), 55443);
////    vecBulbs[0]->connectToBulb(QHostAddress("192.168.0.107"), 55443);
//    for (YeelightBulb::Bulb* bulb: qAsConst(vecBulbs)) {
//        bulb->set_power(false, YeelightBulb::Bulb::Sudden, 1);
//    }
//    QTimer::singleShot(2000, [this](){
//        qDebug() << "SingleShot" << Qt::endl;
//        vecBulbs[0]->resetConnection();
//        QThread::msleep(100);
//        vecBulbs[0]->connectToBulb(QHostAddress("192.168.0.110"), 55443);
//        vecBulbs[0]->set_power(true, YeelightBulb::Bulb::Sudden, 1);

//    });
#endif
}

StateAbstract* EnvironmentSetupHttpServer::onQmlButtonClicked(const BibleBrainRing::Button button)
{
    if (button == BibleBrainRing::ButtonRunCustomServer) {
        runCustomServer();
        return nullptr;
    }
    return EnvironmentSetup::onQmlButtonClicked(button);
}

void EnvironmentSetupHttpServer::runCustomServer()
{
    const QString networksStr = "Write server host and port like this:\n 192.168.0.104:8080. \n\n\nAvailable network list:\n" + getListNetwork();
    const QString hostPort = QInputDialog::getText(nullptr, "Custom server", networksStr);
    const auto list = hostPort.split(":");
    if (list.size() == 2) {
        HttpServer* httpServer = new HttpServer(list.front(), list.back());
        bibleBrainRingServerClassical.reset(new BibleBrainRingServerClassical(httpServer));
        const bool ret = bibleBrainRingServerClassical->initServer();
        const QString address = "Your server address: " + httpServer->getHostPort();
        const QString message = ret ? address : "Http server can't start";
        providerQml->setCurrentHttpServerHostPort(message);
    }
    else{
        emit providerQml->showMessage("Parse error!");
    }
}
