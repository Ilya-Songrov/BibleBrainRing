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

ServerModeAcceptsRegistrations::ServerModeAcceptsRegistrations(QObject *parent) : ServerModeGameAbstract(ServerMode::AcceptsRegistrations, __FUNCTION__, parent)
    , value_notification_client_to_server_registration                ("notification_client_to_server_registration")
{

}

ServerModeAbstract *ServerModeAcceptsRegistrations::stopRegistration()
{
    io->pauseAcceptingClients();
    return new ServerModeSelectingSparringTeams();
}

ServerModeAbstract *ServerModeAcceptsRegistrations::banTeam(const QString &guidTeam)
{
    ServerModeAbstract::bunTeam(guidTeam);
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
        if (objRoot.value(key_method).toString() == value_notification_client_to_server_registration) {
            const auto team = DtoCreator::getTeamDto(objRoot);
            if (getTeam(guidClient).status == TeamStatus::NotValid) {
                changeTeam(team, true);
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

TeamStatus ServerModeAcceptsRegistrations::getTeamStatus(const QString &guidTeam)
{
    return getTeam(guidTeam).status;
}
