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

#include "servermodegameabstract.h"

class ServerModeRunningSparring : public ServerModeGameAbstract
{
public:
    explicit ServerModeRunningSparring(QObject *parent = nullptr);

    virtual ServerModeAbstract* slotResponseFromClient(const QString &guidClient, const QByteArray &arrBytes) override;
    virtual ServerModeAbstract* activateButtonsSparringTeams() override;
    virtual ServerModeAbstract* deactivateButtonsSparringTeams() override;

private:
    const QString value_notification_answer_to_question;
};

