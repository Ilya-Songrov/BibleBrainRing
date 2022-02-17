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

#include "biblebrainringserverclassical.h"

BibleBrainRingServerClassical::BibleBrainRingServerClassical(IODeviceServerAbstract *ioDeviceServerAbstract) : QObject(nullptr)
    , io(ioDeviceServerAbstract)
{
}

BibleBrainRingServerClassical::~BibleBrainRingServerClassical()
{

}

bool BibleBrainRingServerClassical::initServer()
{
    return io->initServer();
}

void BibleBrainRingServerClassical::startRegistration()
{
    io->startAcceptingClients();
}

void BibleBrainRingServerClassical::stopRegistration()
{
    io->stopAcceptingClients();
}

void BibleBrainRingServerClassical::addTeamsToBattle(const QVector<QString>& vecGuidTeam)
{
    QVector<DtoTeamActivationForBattleServerRq> vec;
    for (const QString& guid: vecGuidTeam) {
        DtoTeamActivationForBattleServerRq dto;
        dto.guid = guid;
        dto.isActive = true;
        vec.append(dto);
        changeTeam(guid, TeamStatus::InBattle);
    }
    io->sendToClients(vec);
}

void BibleBrainRingServerClassical::removeTeamsFromBattle()
{
    QVector<DtoTeamActivationForBattleServerRq> vec;
    const auto vecTeams = getTeams(TeamStatus::InBattle);
    for (const TeamDto& t: vecTeams) {
        DtoTeamActivationForBattleServerRq dto;
        dto.guid = t.guid;
        dto.isActive = false;
        vec.append(dto);
    }
    io->sendToClients(vec);
}

QVector<QString> BibleBrainRingServerClassical::getTeamsInBattle()
{
}

void BibleBrainRingServerClassical::onConnectNewTeam(std::function<void (const TeamDto &)> function)
{
    functionConnectNewTeam = function;
}

void BibleBrainRingServerClassical::onTeamDtoChanged(std::function<void (const TeamDto &)> function)
{
    functionTeamDtoChanged = function;
}

void BibleBrainRingServerClassical::appendTeam(const TeamDto& team)
{
    listTeams.append(team);
    if (functionTeamDtoChanged) {
        functionTeamDtoChanged (team);
    }
}

void BibleBrainRingServerClassical::changeTeam(const TeamDto& team, const bool runCallback)
{
    for (TeamDto &t: listTeams) {
        if (t.guid == team.guid) {
            t = team;
            if (runCallback && functionTeamDtoChanged) {
                functionTeamDtoChanged (team);
            }
            return;
        }
    }
}

void BibleBrainRingServerClassical::changeTeam(const QString& guidTeam, const TeamStatus teamStatus, const bool runCallback)
{
    auto team = DtoCreator::getTeamDto(guidTeam);
    team.status = teamStatus;
    changeTeam(team, runCallback);
}

TeamDto BibleBrainRingServerClassical::getTeam(const QString& guidTeam)
{
    for (const TeamDto &t: qAsConst(listTeams)) {
        if (t.guid == guidTeam) {
            return t;
        }
    }
    return {};
}

QVector<TeamDto> BibleBrainRingServerClassical::getTeams(const TeamStatus teamStatus)
{
    QVector<TeamDto> vec;
    for (const TeamDto &t: qAsConst(listTeams)) {
        if (t.status == teamStatus) {
            vec.append(t);
        }
    }
    return vec;
}



