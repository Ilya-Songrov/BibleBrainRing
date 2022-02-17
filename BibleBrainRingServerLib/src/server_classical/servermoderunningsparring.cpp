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

#include "servermoderunningsparring.h"

ServerModeRunningSparring::ServerModeRunningSparring(QObject *parent) : ServerModeGameAbstract(ServerMode::RunningSparring, __FUNCTION__, parent)
  , notification_server_to_client_change_button_state("notification_server_to_client_change_button_state")
  , notification_server_to_client_start_time_for_question("notification_server_to_client_start_time_for_question")
  , notification_server_to_client_round_result("notification_server_to_client_round_result")
  , request_client_to_server_answer_to_question("request_client_to_server_answer_to_question")
{
    timer.setSingleShot(true);
    connect(&timer, &QTimer::timeout, this, &ServerModeRunningSparring::slotTimeout);
    s.openRound(vecSparringTeams);
}

ServerModeAbstract *ServerModeRunningSparring::slotResponseFromClient(const QString &guidClient, const QByteArray &arrBytes)
{
    const QJsonDocument doc = QJsonDocument::fromJson(arrBytes);
    InformationConsolePrinter::printArrAndMessage(doc.isEmpty() ? arrBytes : doc.toJson(), "SERVER <--- CLIENT", print_color, arrBytes.isEmpty());
    const QJsonObject objRoot = doc.object();
    const bool isItRequest = objRoot.value(key_id) != QJsonValue::Null;
    if (isItRequest) {
        if (objRoot.value(key_method).toString() == request_client_to_server_answer_to_question) {
            const auto team = getTeam(guidClient);
            if (team.status == TeamStatus::InBattle) {
                changeTeam(team, false);
            }
            else{
                qWarning() << QString("Server already have team info about this client (%1)" ).arg(guidClient) << Qt::endl;
            }
        }
    }
    return nullptr;
}

ServerModeAbstract *ServerModeRunningSparring::activateButtonsSparringTeams()
{
    sendToSparringTeams(notification_server_to_client_change_button_state, true);
    return nullptr;
}

ServerModeAbstract *ServerModeRunningSparring::deactivateButtonsSparringTeams()
{
    sendToSparringTeams(notification_server_to_client_change_button_state, false);
    return nullptr;
}

ServerModeAbstract *ServerModeRunningSparring::startRound(const int timeoutMsecs)
{
    timer.start(timeoutMsecs);
    sendToSparringTeams(notification_server_to_client_start_time_for_question, QJsonObject{{"timeoutMsecs", timeoutMsecs}});
    return nullptr;
}

ServerModeAbstract *ServerModeRunningSparring::finishSparring()
{
    s.closeRound();
    return new ServerModeShowingSparringResult();
}

ServerModeAbstract *ServerModeRunningSparring::addSparringNote(const QString &note)
{
    // TODO: write me
    return nullptr;
}

ServerModeAbstract *ServerModeRunningSparring::changeTeamScore(const QString &guidTeam, const double score)
{

}

void ServerModeRunningSparring::slotTimeout()
{

}

