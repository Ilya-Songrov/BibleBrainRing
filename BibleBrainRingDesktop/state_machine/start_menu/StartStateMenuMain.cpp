/**************************************************************************
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 as published by the Free Software
** Foundation with exceptions as appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/.
**
**************************************************************************/

#include "StartStateMenuMain.h"

StartStateMenuMain::StartStateMenuMain(QObject *parent) : StateAbstract(__FUNCTION__, parent)
{
    providerQml->setCurrentAppState(BibleBrainRing::StartMenu);
    providerQml->setCurrentAppMode(BibleBrainRing::AppMode::AppModeNone);
    listTeamsInResult->clear();
}

StateAbstract *StartStateMenuMain::onQmlButtonClicked(const BibleBrainRing::Button button)
{
    if (button == BibleBrainRing::ButtonStartServerWifi) {
        providerQml->setCurrentAppMode(BibleBrainRing::AppMode::AppModeServerWifi);
        emit providerQml->showMessage("Write me, please");
//        static TcpServer tcpServer("127.0.0.1", "9090");
//        serverClassical.reset(new BibleBrainRingServerClassical(&tcpServer));
    }
    else if (button == BibleBrainRing::ButtonStartServerBluetooth) {
        providerQml->setCurrentAppMode(BibleBrainRing::AppMode::AppModeServerBluetooth);
        emit providerQml->showMessage("Write me, please");
    }
    else if (button == BibleBrainRing::ButtonStartServerHttp) {
        providerQml->setCurrentAppMode(BibleBrainRing::AppMode::AppModeServerHttp);
#ifdef QT_DEBUG
        HttpServer* httpServer = new HttpServer("192.168.1.101", "8282");
#else
        HttpServer* httpServer = new HttpServer(QHostAddress(QHostAddress::Any).toString(), "8080");
#endif
        bibleBrainRingServerClassical.reset(new BibleBrainRingServerClassical(httpServer));
        const bool ret = bibleBrainRingServerClassical->initServer();
        const QString address = "Your server address: " + httpServer->getHostPort();
        const QString message = ret ? address : "Http server can't start";
        providerQml->setCurrentHttpServerHostPort(message);
        if (ret) {
            return new EnvironmentSetupHttpServer();
        }
        emit providerQml->showMessage(message);
    }
    else if (button == BibleBrainRing::ButtonStartClientWifi) {
        providerQml->setCurrentAppMode(BibleBrainRing::AppMode::AppModeClientWifi);
        emit providerQml->showMessage("Write me, please");
    }
    else if (button == BibleBrainRing::ButtonStartClientBluetooth) {
        providerQml->setCurrentAppMode(BibleBrainRing::AppMode::AppModeClientBluetooth);
        emit providerQml->showMessage("Write me, please");
    }
    else if (button == BibleBrainRing::ButtonStartOnlyProgram) {
        providerQml->setCurrentAppMode(BibleBrainRing::AppMode::AppModeOnlyProgram);
        return new EnvironmentSetup("write me");
    }
    return nullptr;
}
