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

class ServerModeRunningGameSession : public ServerModeAbstract
{
public:
    explicit ServerModeRunningGameSession(QObject *parent = nullptr);

    virtual ServerModeAbstract* changeQuestionStatus(const QString &question, const QuestionStatus questionStatus) override;

    virtual ServerModeAbstract* slotResponseFromClient(const QString &guidClient, const QByteArray &arrBytes) override;
    virtual ServerModeAbstract* slotClientStatusChanged(const QString &guidClient, const IODeviceServerAbstract::ClientStatus clientStatus) override;
};

