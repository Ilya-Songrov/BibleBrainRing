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

#pragma once

#include <QJsonDocument>
#include <QJsonObject>

#include "dtos/AllDtos.hpp"
#include "iodevice/iodeviceserverabstract.h"

class BibleBrainRingServerClassical : public QObject
{
    Q_OBJECT
public:
    explicit BibleBrainRingServerClassical(IODeviceServerAbstract *ioDeviceServerAbstract);
    ~BibleBrainRingServerClassical();

    bool initServer();

    void startRegistration();
    void stopRegistration();

    void addTeamsToBattle(const QVector<QString>& vecGuidTeam);
    void removeTeamsFromBattle();
    QVector<QString> getTeamsInBattle();

    TeamDto getTeam(const QString& guidTeam);

    // callbacks:
    void onConnectNewTeam   (std::function<void(const TeamDto &)> function);
    void onTeamDtoChanged   (std::function<void(const TeamDto &)> function);

private:
    void appendTeam(const TeamDto &team);
    void changeTeam(const TeamDto &team, const bool runCallback = false);
    void changeTeam(const QString& guidTeam, const TeamStatus teamStatus, const bool runCallback = false);
    QVector<TeamDto> getTeams(const TeamStatus teamStatus);


private:
    IODeviceServerAbstract *io;
    QList<TeamDto> listTeams;
    std::function<void(const TeamDto &)>    functionConnectNewTeam;
    std::function<void(const TeamDto &)>    functionTeamDtoChanged;
//    ServerModeAbstract* _currentServerMode;
};

