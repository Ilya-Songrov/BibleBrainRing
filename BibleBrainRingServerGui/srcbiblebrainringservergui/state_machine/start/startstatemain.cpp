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

StartStateMain::StartStateMain(QObject *parent) : StateAbstract(__FUNCTION__, parent)
{
    providerQml->setCurrentAppState(BibleBrainRing::Start);
}

StateAbstract *StartStateMain::onQmlButtonClicked(const BibleBrainRing::Button button)
{
    bool successInit = false;
    if (button == BibleBrainRing::ButtonStartServerWifi) {
        static TcpServer tcpServer("127.0.0.1", "9090");
        serverClassical.reset(new BibleBrainRingServerClassical(&tcpServer));
        successInit = serverClassical->initServer();
    }
    else if (button == BibleBrainRing::ButtonStartServerBluetooth) {

    }

    if (successInit) {
        return new RegistrationStateMain();
    }
    return nullptr;
}
