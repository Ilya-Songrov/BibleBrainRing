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

#include "biblebrainringserverlib/server_classical/servermodeacceptsregistrations.h"

ServerModeAcceptsRegistrations::ServerModeAcceptsRegistrations(QObject *parent) : ServerModeAbstract(ServerMode::AcceptsRegistrations, __FUNCTION__, parent)
    , value_notification_TeamDto                ("notification_TeamDto")
    , value_notification_TeamRegistrationDto    ("notification_TeamRegistrationDto")
{

}

ServerModeAbstract *ServerModeAcceptsRegistrations::stopRegistration()
{
    io->pauseAcceptingClients();
    return new ServerModeRunningGameSession();
}

ServerModeAbstract *ServerModeAcceptsRegistrations::banTeam(const QString &guidTeam)
{
    ServerModeAbstract::bunTeam(guidTeam);
    return nullptr;
}

ServerModeAbstract *ServerModeAcceptsRegistrations::changeTeamScore(const QString &guidTeam, const double score)
{
    auto team   = getTeam(guidTeam);
    team.score  = score;
    changeTeam(team);
    return nullptr;
}

ServerModeAbstract *ServerModeAcceptsRegistrations::loadListQuestions(const QStringList &questions)
{
    q.loadQuestions(questions);
    return nullptr;
}

ServerModeAbstract *ServerModeAcceptsRegistrations::slotJoinedClient(const QString &guidClient)
{
    const auto team = DtoCreator::getTeamDto(guidClient, TeamStatus::NotValid);
    changeTeam(team, false);
    if (functionConnectNewTeam) {
        functionConnectNewTeam (team);
    }
    return nullptr;
}

ServerModeAbstract *ServerModeAcceptsRegistrations::slotResponseFromClient(const QString &guidClient, const QByteArray &arrBytes)
{
    const QJsonDocument doc = QJsonDocument::fromJson(arrBytes);
    InformationConsolePrinter::printArrAndMessage(doc.isEmpty() ? arrBytes : doc.toJson(), "SERVER <--- CLIENT", print_color, arrBytes.isEmpty());
    const QJsonObject objRoot = doc.object();
    const bool isItNotification = objRoot.value(key_id) == QJsonValue::Null;
    if (isItNotification) {
        if (objRoot.value(key_method).toString() == value_notification_TeamDto) {
            const auto team = DtoCreator::getTeamDto(objRoot);
            if (getTeam(guidClient).status == TeamStatus::NotValid) {
                changeTeam(team, false);
            }
            else{
                qWarning() << QString("Server already have team info about this client (%1)" ).arg(guidClient) << Qt::endl;
            }
        }
        else if(objRoot.value(key_method).toString() == value_notification_TeamRegistrationDto){
            const auto team = DtoCreator::getTeamDto(objRoot);
            if (getTeam(guidClient).status == TeamStatus::NotValid) {
                changeTeam(team, false);
            }
            else{
                qWarning() << QString("Server already have team info about this client (%1)" ).arg(guidClient) << Qt::endl;
            }
        }
    }
    return nullptr;
}

ServerModeAbstract *ServerModeAcceptsRegistrations::slotClientStatusChanged(const QString &guidClient, const IODeviceServerAbstract::ClientStatus clientStatus)
{
    changeClientStatus(guidClient, clientStatus);
    return nullptr;
}

QVector<QString> ServerModeAcceptsRegistrations::getSparringTeams()
{
    // TODO: write me
    return {};
}

TeamStatus ServerModeAcceptsRegistrations::getTeamStatus(const QString &guidTeam)
{
    return getTeam(guidTeam).status;
}

int ServerModeAcceptsRegistrations::getTeamScore(const QString &guidTeam)
{
    return getTeam(guidTeam).score;
}
