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

#include "servermodeabstract.h"
#include "all_server_modes.h"

class ServerModeAcceptsRegistrations : public ServerModeAbstract
{
public:
    explicit ServerModeAcceptsRegistrations(QObject *parent = nullptr);

    virtual ServerModeAbstract* stopRegistration() override;

    virtual ServerModeAbstract* banTeam(const QString &guidTeam) override;
    virtual ServerModeAbstract* changeTeamScore(const QString &guidTeam, const double score) override;

    virtual ServerModeAbstract* loadListQuestions(const QStringList &questions) override;

    virtual ServerModeAbstract* slotJoinedClient(const QString &guidClient) override;
    virtual ServerModeAbstract* slotResponseFromClient(const QString &guidClient, const QByteArray &arrBytes) override;
    virtual ServerModeAbstract* slotClientStatusChanged(const QString &guidClient, const IODeviceServerAbstract::ClientStatus clientStatus) override;

    virtual QVector<QString> getSparringTeams() override;
    virtual TeamStatus getTeamStatus(const QString &guidTeam) override;
    virtual int getTeamScore(const QString &guidTeam) override;

private:
    const QString value_notification_TeamDto;
    const QString value_notification_TeamRegistrationDto;
};

