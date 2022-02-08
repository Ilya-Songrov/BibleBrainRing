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

#include "startstatemain.h"

StartStateMenuMain::StartStateMenuMain(QObject *parent) : StateAbstract(__FUNCTION__, parent)
{
    providerQml->setCurrentAppState(BibleBrainRing::StartMenu);
}

StateAbstract *StartStateMenuMain::onQmlButtonClicked(const BibleBrainRing::Button button)
{
    if (button == BibleBrainRing::ButtonStartServerWifi) {
        emit providerQml->showMessage("Write me, please");
//        static TcpServer tcpServer("127.0.0.1", "9090");
//        serverClassical.reset(new BibleBrainRingServerClassical(&tcpServer));
    }
    else if (button == BibleBrainRing::ButtonStartServerBluetooth) {
        emit providerQml->showMessage("Write me, please");
    }
    else if (button == BibleBrainRing::ButtonStartServerHttp) {
        return new RegistrationStateMain();
    }
    else if (button == BibleBrainRing::ButtonStartClientWifi) {
        emit providerQml->showMessage("Write me, please");
    }
    else if (button == BibleBrainRing::ButtonStartClientBluetooth) {
        emit providerQml->showMessage("Write me, please");
    }
    else if (button == BibleBrainRing::ButtonStartOnlyProgram) {
        emit providerQml->showMessage("Write me, please");
    }
    return nullptr;
}
