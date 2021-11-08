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

#include "biblebrainringserverlib/server_classical/servermoderunningsparring.h"

ServerModeRunningSparring::ServerModeRunningSparring(QObject *parent) : ServerModeGameAbstract(ServerMode::RunningSparring, __FUNCTION__, parent)
  , value_notification_answer_to_question("notification_answer_to_question")
{

}

ServerModeAbstract *ServerModeRunningSparring::slotResponseFromClient(const QString &guidClient, const QByteArray &arrBytes)
{
    const QJsonDocument doc = QJsonDocument::fromJson(arrBytes);
    InformationConsolePrinter::printArrAndMessage(doc.isEmpty() ? arrBytes : doc.toJson(), "SERVER <--- CLIENT", print_color, arrBytes.isEmpty());
    const QJsonObject objRoot = doc.object();
    const bool isItNotification = objRoot.value(key_id) == QJsonValue::Null;
    if (isItNotification) {
        if (objRoot.value(key_method).toString() == value_notification_answer_to_question) {
            const auto team = DtoCreator::getTeamDto(objRoot);
            if (getTeam(guidClient).status == TeamStatus::NotValid) {
                changeTeam(team, false);
            }
            else{
                qWarning() << QString("Server already have team info about this client (%1)" ).arg(guidClient) << Qt::endl;
            }
        }
//        else if(objRoot.value(key_method).toString() == value_notification_TeamRegistrationDto){
//            const auto team = DtoCreator::getTeamDto(objRoot);
//            if (getTeam(guidClient).status == TeamStatus::NotValid) {
//                changeTeam(team, false);
//            }
//            else{
//                qWarning() << QString("Server already have team data about this client (%1)" ).arg(guidClient) << Qt::endl;
//            }
//        }
    }
    return nullptr;
}

ServerModeAbstract *ServerModeRunningSparring::activateButtonsSparringTeams()
{

}

ServerModeAbstract *ServerModeRunningSparring::deactivateButtonsSparringTeams()
{

}
