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
#include "iodevice/http/HttpServer.hpp" //TODO: delete me
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
    void addTeamToBattle(const QString& guidTeam);
    void removeTeamFromBattle(const QString& guidTeam);
    QVector<TeamDto> getTeamsInBattle();

    static TeamDto getTeam(QString guidTeam);

    // callbacks:
    void onConnectNewTeam   (std::function<void(const TeamDto)> function);
    void onPressedButton    (std::function<void(const DtoButtonPressedRq)> function);

signals:
    void signalConnectNewTeam(TeamDto);
    void signalPressedButton(DtoButtonPressedRq);

private slots:
    void slotJoinedClient(const DtoTeamRegistrationClientRs teamRs);
    void slotButtonPressed(const DtoButtonPressedRq buttonPressedRq);

private:
    void appendTeam(const TeamDto &team);
    void changeTeam(const TeamDto &team);
    void changeTeam(const QString& guidTeam, const TeamStatus teamStatus);
    QVector<TeamDto> getTeams(const TeamStatus teamStatus);


private:
    static QList<TeamDto> listTeams;
    IODeviceServerAbstract *io;
    std::function<void(const TeamDto)>              functionConnectNewTeam;
    std::function<void(const DtoButtonPressedRq)>   functionPressedButton;
};

