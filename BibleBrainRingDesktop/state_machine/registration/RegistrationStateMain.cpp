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

#include "RegistrationStateMain.h"

RegistrationStateMain::RegistrationStateMain(QObject *parent)
    : StateAbstract(__FUNCTION__, parent)
{
    providerQml->setCurrentAppState(BibleBrainRing::Registration);
    bibleBrainRingServerClassical->startRegistration();
    connect(bibleBrainRingServerClassical.get(), &BibleBrainRingServerClassical::signalConnectNewTeam,
            this, &RegistrationStateMain::slotConnectNewTeam, Qt::BlockingQueuedConnection);



#ifdef QT_DEBUG
//    QTimer::singleShot(100, [](){
//        qDebug() << "SingleShot" << Qt::endl;
//        TeamDto team;
//        team.guid        = "guid";
//        team.name        = "name";
//        team.color       = "green";
//        team.score       = 2;
//        team.position    = 3;
//        team.status      = TeamStatus::NotValid;
//        listTeamsRegistration->appendTeam(team);
//        team.color      = "blue";
//        team.status      = TeamStatus::Lost;
//        listTeamsRegistration->appendTeam(team);
//        QTimer::singleShot(1000, [team](){
//            qDebug() << "SingleShot" << Qt::endl;
//            listTeamsRegistration->appendTeam(team);
//        });
//        QTimer::singleShot(2000, [team](){
//            qDebug() << "SingleShot" << Qt::endl;
//            listTeamsRegistration->appendTeam(team);
//        });
//    });
#endif
}

StateAbstract *RegistrationStateMain::onQmlButtonClicked(const BibleBrainRing::Button button)
{
    bibleBrainRingServerClassical->stopRegistration();
    if (button == BibleBrainRing::ButtonComeback) {
        // TODO: add: do you want to lose all progress?
        return new EnvironmentSetup();
    }
    else if (button == BibleBrainRing::ButtonNext) {
        return new GameSession();
    }
    return nullptr;
}

void RegistrationStateMain::slotConnectNewTeam(TeamDto team)
{
    listTeamsRegistration->appendTeam(team);
}
