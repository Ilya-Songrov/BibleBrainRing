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

#include "server_classical/servermoderunninggamesession.h"

ServerModeRunningGameSession::ServerModeRunningGameSession(QObject *parent) : ServerModeAbstract(ServerMode::RunningGameSession, __FUNCTION__, parent)
{

}

ServerModeAbstract *ServerModeRunningGameSession::changeQuestionStatus(const QString &question, const QuestionStatus questionStatus)
{
    q.changeQuestionStatus(question, questionStatus);
    return nullptr;
}

ServerModeAbstract *ServerModeRunningGameSession::slotResponseFromClient(const QString &guidClient, const QByteArray &arrBytes)
{

}

ServerModeAbstract *ServerModeRunningGameSession::slotClientStatusChanged(const QString &guidClient, const IODeviceServerAbstract::ClientStatus clientStatus)
{
    changeClientStatus(guidClient, clientStatus);
    return nullptr;
}
