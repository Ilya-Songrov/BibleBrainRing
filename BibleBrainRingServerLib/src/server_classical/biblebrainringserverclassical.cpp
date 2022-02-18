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

QList<TeamDto> BibleBrainRingServerClassical::listTeams;

BibleBrainRingServerClassical::BibleBrainRingServerClassical(IODeviceServerAbstract *ioDeviceServerAbstract) : QObject(nullptr)
  , io(ioDeviceServerAbstract)
  , functionConnectNewTeam(nullptr)
  , functionPressedButton(nullptr)
{
    connect(io, &IODeviceServerAbstract::joinedClient, this, &BibleBrainRingServerClassical::slotJoinedClient, Qt::DirectConnection);
    connect(io, &IODeviceServerAbstract::buttonPressed, this, &BibleBrainRingServerClassical::slotButtonPressed, Qt::DirectConnection);
    connect(io, &IODeviceServerAbstract::refereeReset, this, &BibleBrainRingServerClassical::slotRefereeReset, Qt::DirectConnection);
    connect(io, &IODeviceServerAbstract::refereeStartTime, this, &BibleBrainRingServerClassical::slotRefereeStartTime, Qt::DirectConnection);
}

BibleBrainRingServerClassical::~BibleBrainRingServerClassical()
{
    if (io) {
        delete io;
    }
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

void BibleBrainRingServerClassical::addTeamToBattle(const QString& guidTeam)
{
    TeamDto team = getTeam(guidTeam);
    DtoTeamActivationForBattleServerRq dto;
    dto.guid = team.guid;
    dto.isActive = true;
    changeTeam(guidTeam, TeamStatus::InBattle);
    io->sendToClients(dto);
}

void BibleBrainRingServerClassical::removeTeamFromBattle(const QString& guidTeam)
{
    changeTeam(guidTeam, TeamStatus::WaitingForTheNextRound);
    TeamDto team = getTeam(guidTeam);
    DtoTeamActivationForBattleServerRq dto;
    dto.guid = team.guid;
    dto.isActive = false;
    io->sendToClients(dto);
}

QVector<TeamDto> BibleBrainRingServerClassical::getTeamsInBattle()
{
    return getTeams(TeamStatus::InBattle);
}

void BibleBrainRingServerClassical::onConnectNewTeam(std::function<void (const TeamDto)> function)
{
    functionConnectNewTeam = function;
}

void BibleBrainRingServerClassical::onPressedButton(std::function<void (const DtoButtonPressedRq)> function)
{
    functionPressedButton = function;
}

void BibleBrainRingServerClassical::slotJoinedClient(const DtoTeamRegistrationClientRs teamRs)
{
    TeamDto team = DtoCreator::getTeamDto(teamRs.guid, teamRs.name, teamRs.color);
    team.status = TeamStatus::Registered;
    appendTeam(team);
}

void BibleBrainRingServerClassical::slotButtonPressed(const DtoButtonPressedRq buttonPressedRq)
{
    if (functionPressedButton) {
        functionPressedButton (buttonPressedRq);
    }
    emit signalPressedButton(buttonPressedRq);
}

void BibleBrainRingServerClassical::slotRefereeReset(qint64 time)
{
    emit signalRefereeReset(time);
}

void BibleBrainRingServerClassical::slotRefereeStartTime(qint64 time)
{
    emit signalRefereeStartTime(time);
}

void BibleBrainRingServerClassical::appendTeam(const TeamDto& team)
{
    listTeams.append(team);
    if (functionConnectNewTeam) {
        functionConnectNewTeam (team);
    }
    emit signalConnectNewTeam(team);
}

void BibleBrainRingServerClassical::changeTeam(const TeamDto& team)
{
    for (TeamDto &t: listTeams) {
        if (t.guid == team.guid) {
            t = team;
            return;
        }
    }
}

void BibleBrainRingServerClassical::changeTeam(const QString& guidTeam, const TeamStatus teamStatus)
{
    auto team = DtoCreator::getTeamDto(guidTeam);
    team.status = teamStatus;
    changeTeam(team);
}

TeamDto BibleBrainRingServerClassical::getTeam(QString guidTeam)
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



