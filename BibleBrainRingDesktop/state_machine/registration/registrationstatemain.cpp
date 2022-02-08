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

#include "registrationstatemain.h"

RegistrationStateMain::RegistrationStateMain(QObject *parent) : StateAbstract(__FUNCTION__, parent)
{
    providerQml->setCurrentAppState(BibleBrainRing::Registration);
//    serverClassical->startRegistration();

//    serverClassical->onConnectNewTeam([](const TeamDto &team){ qDebug() << "new team:" << team.guid << Qt::endl;});
//    QTimer::singleShot(4000, [this](){
//        qDebug() << "SingleShot1" << Qt::endl;
//        serverClassical->stopRegistration();
//        QTimer::singleShot(4000, [this](){
//            qDebug() << "SingleShot2" << Qt::endl;
//            serverClassical->startRegistration();
//        });
//    });


    QTimer::singleShot(100, [this](){
        qDebug() << "SingleShot" << Qt::endl;

    });
}

StateAbstract *RegistrationStateMain::onQmlButtonClicked(const BibleBrainRing::Button button)
{
    if (button == BibleBrainRing::ButtonComeback) {
        // TODO: add: do you want to lose all progress?
        return new StartStateMenuMain();
    }
    return nullptr;
}
