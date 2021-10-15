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

#include "biblebrainringserverlib/server_classical/servermodeabstract.h"

IODeviceServerAbstract* ServerModeAbstract::io                                          = nullptr;
Questions ServerModeAbstract::q                                                         ;
QList<TeamDto> ServerModeAbstract::listTeams                                            ;
std::function<void(const TeamDto &)>    ServerModeAbstract::functionConnectNewTeam      = nullptr;
std::function<void(const TeamDto &)>    ServerModeAbstract::functionTeamDtoChanged      = nullptr;

const QString ServerModeAbstract::print_color                                           = { "192;61;205" };
const QString ServerModeAbstract::key_method                                            = { "method" };
const QString ServerModeAbstract::key_params                                            = { "params" };
const QString ServerModeAbstract::key_id                                                = { "id" };

ServerModeAbstract::ServerModeAbstract(const ServerMode mode, const QString &objectName, QObject *parent) : QObject(parent)
  , _mode(mode)
{
    setObjectName(objectName);
}

ServerModeAbstract *ServerModeAbstract::initServer()
{
    qWarning() << "Not processed:" << "State: " + objectName() << "function: " + QString(Q_FUNC_INFO)
               << QDateTime::currentDateTime().toString("yyyy:MM:dd - hh:mm:ss:zzz") << Qt::endl;
    return nullptr;
}


ServerModeAbstract *ServerModeAbstract::startRegistration()
{
    qWarning() << "Not processed:" << "State: " + objectName() << "function: " + QString(Q_FUNC_INFO)
               << QDateTime::currentDateTime().toString("yyyy:MM:dd - hh:mm:ss:zzz") << Qt::endl;
    return nullptr;
}

ServerModeAbstract *ServerModeAbstract:: stopRegistration()
{
    qWarning() << "Not processed:" << "State: " + objectName() << "function: " + QString(Q_FUNC_INFO)
               << QDateTime::currentDateTime().toString("yyyy:MM:dd - hh:mm:ss:zzz") << Qt::endl;
    return nullptr;
}

ServerModeAbstract *ServerModeAbstract::setSparringTeams(const QVector<QString> &vecGuidTeam)
{
    qWarning() << "Not processed:" << "State: " + objectName() << "function: " + QString(Q_FUNC_INFO)
               << "vecGuidTeam:" << vecGuidTeam
               << QDateTime::currentDateTime().toString("yyyy:MM:dd - hh:mm:ss:zzz") << Qt::endl;
    return nullptr;
}


ServerModeAbstract *ServerModeAbstract::activateButtonsSparringTeams()
{
    qWarning() << "Not processed:" << "State: " + objectName() << "function: " + QString(Q_FUNC_INFO)
               << QDateTime::currentDateTime().toString("yyyy:MM:dd - hh:mm:ss:zzz") << Qt::endl;
    return nullptr;
}

ServerModeAbstract *ServerModeAbstract::banTeam(const QString &guidTeam)
{
    qWarning() << "Not processed:" << "State: " + objectName() << "function: " + QString(Q_FUNC_INFO)
               << QString("guidTeam: %1").arg(guidTeam)
               << QDateTime::currentDateTime().toString("yyyy:MM:dd - hh:mm:ss:zzz") << Qt::endl;
    return nullptr;
}

ServerModeAbstract *ServerModeAbstract::changeTeamScore(const QString &guidTeam, const double score)
{
    qWarning() << "Not processed:" << "State: " + objectName() << "function: " + QString(Q_FUNC_INFO)
               << QString("guidTeam: %1").arg(guidTeam)
               << QString("score: %1").arg(score)
               << QDateTime::currentDateTime().toString("yyyy:MM:dd - hh:mm:ss:zzz") << Qt::endl;
    return nullptr;
}

ServerModeAbstract *ServerModeAbstract::loadListQuestions(const QStringList &questions)
{
    qWarning() << "Not processed:" << "State: " + objectName() << "function: " + QString(Q_FUNC_INFO)
               << "questions:" << questions
               << QDateTime::currentDateTime().toString("yyyy:MM:dd - hh:mm:ss:zzz") << Qt::endl;
    return nullptr;
}

ServerModeAbstract *ServerModeAbstract::changeQuestionStatus(const QString &question, const QuestionStatus questionStatus)
{
    qWarning() << "Not processed:" << "State: " + objectName() << "function: " + QString(Q_FUNC_INFO)
               << QString("question: %1").arg(question)
               << "questionStatus:" << questionStatus
               << QDateTime::currentDateTime().toString("yyyy:MM:dd - hh:mm:ss:zzz") << Qt::endl;
    return nullptr;
}

ServerModeAbstract *ServerModeAbstract::slotJoinedClient(const QString &guidClient)
{
    qWarning() << "Not processed:" << "State: " + objectName() << "function: " + QString(__FUNCTION__)
               << QString("guidClient: %1").arg(guidClient)
               << QDateTime::currentDateTime().toString("yyyy:MM:dd - hh:mm:ss:zzz") << Qt::endl;
    return nullptr;
}

ServerModeAbstract *ServerModeAbstract::slotResponseFromClient(const QString &guidClient, const QByteArray &arrBytes)
{
    qWarning() << "Not processed:" << "State: " + objectName() << "function: " + QString(__FUNCTION__)
               << QString("guidClient: %1").arg(guidClient)
               << "arrBytes:" << qPrintable(arrBytes)
               << QDateTime::currentDateTime().toString("yyyy:MM:dd - hh:mm:ss:zzz") << Qt::endl;
    return nullptr;
}

ServerModeAbstract *ServerModeAbstract::slotClientStatusChanged(const QString &guidClient, const IODeviceServerAbstract::ClientStatus clientStatus)
{
    qWarning() << "Not processed:" << "State: " + objectName() << "function: " + QString(__FUNCTION__)
               << QString("guidClient: %1").arg(guidClient)
               << "clientStatus:" << clientStatus
               << QDateTime::currentDateTime().toString("yyyy:MM:dd - hh:mm:ss:zzz") << Qt::endl;
    return nullptr;
}

QVector<QString> ServerModeAbstract::getSparringTeams()
{
    qWarning() << "Not processed:" << "State: " + objectName() << "function: " + QString(__FUNCTION__)
               << QDateTime::currentDateTime().toString("yyyy:MM:dd - hh:mm:ss:zzz") << Qt::endl;
    return {};
}

TeamStatus ServerModeAbstract::getTeamStatus(const QString &guidTeam)
{
    qWarning() << "Not processed:" << "State: " + objectName() << "function: " + QString(__FUNCTION__)
               << QString("guidTeam: %1").arg(guidTeam)
               << QDateTime::currentDateTime().toString("yyyy:MM:dd - hh:mm:ss:zzz") << Qt::endl;
    return {};
}

int ServerModeAbstract::getTeamScore(const QString &guidTeam)
{
    qWarning() << "Not processed:" << "State: " + objectName() << "function: " + QString(__FUNCTION__)
               << QString("guidTeam: %1").arg(guidTeam)
               << QDateTime::currentDateTime().toString("yyyy:MM:dd - hh:mm:ss:zzz") << Qt::endl;
    return {};
}

ServerMode ServerModeAbstract::getCurrentServerMode()
{
    return _mode;
}

void ServerModeAbstract::onConnectNewTeam(std::function<void (const TeamDto &)> function)
{
    functionConnectNewTeam = function;
}

void ServerModeAbstract::onTeamDtoChanged(std::function<void (const TeamDto &)> function)
{
    functionTeamDtoChanged = function;
}

void ServerModeAbstract::bunTeam(const QString &guidTeam)
{
    auto team   = getTeam(guidTeam);
    team.status = TeamStatus::Banned;
    changeTeam(team);
}

void ServerModeAbstract::changeClientStatus(const QString &guidClient, const IODeviceServerAbstract::ClientStatus clientStatus)
{
    auto team = DtoCreator::getTeamDto(guidClient);
    if (clientStatus == IODeviceServerAbstract::Undefined) {
        team.status = TeamStatus::None;
    }
    else if (clientStatus == IODeviceServerAbstract::Connected) {
        team = DtoCreator::getTeamDto(guidClient, TeamStatus::NotValid);
    }
    else if (clientStatus == IODeviceServerAbstract::Disconnected) {
        team.status = TeamStatus::Lost;
    }
    changeTeam(team, true);
}

void ServerModeAbstract::changeTeam(const TeamDto &team, const bool runCallback)
{
    for (TeamDto &t: listTeams) {
        if (t.guid == team.guid) {
            t = team;
            if (runCallback) {
                functionTeamDtoChanged (team);
            }
            return;
        }
    }
    listTeams.append(team);
}

TeamDto ServerModeAbstract::getTeam(const QString &guidTeam)
{
    for (const TeamDto &t: qAsConst(listTeams)) {
        if (t.guid == guidTeam) {
            return t;
        }
    }
    return {};
}
