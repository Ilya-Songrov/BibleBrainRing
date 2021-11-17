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

#include <QTimer>

#include "servermodegameabstract.h"
#include "all_server_modes.h"

class ServerModeRunningSparring : public ServerModeGameAbstract
{

public:
    explicit ServerModeRunningSparring(QObject *parent = nullptr);

    virtual ServerModeAbstract* slotResponseFromClient(const QString &guidClient, const QByteArray &arrBytes) override;
    virtual ServerModeAbstract* activateButtonsSparringTeams() override;
    virtual ServerModeAbstract* deactivateButtonsSparringTeams() override;
    virtual ServerModeAbstract* startRound(const int timeoutMsecs) override;
    virtual ServerModeAbstract* finishSparring() override;
    virtual ServerModeAbstract* addSparringNote(const QString &note) override;
    virtual ServerModeAbstract* changeTeamScore(const QString &guidTeam, const double score) override;

private:
    inline bool isCurrentRoundFinished() { return timer.isActive(); };

    void slotTimeout();

private:
    const QString notification_server_to_client_change_button_state;
    const QString notification_server_to_client_start_time_for_question;
    const QString notification_server_to_client_round_result;
    const QString request_client_to_server_answer_to_question;
    QTimer timer;
};

