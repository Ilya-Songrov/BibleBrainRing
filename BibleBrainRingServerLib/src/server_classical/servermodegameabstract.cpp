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

#include "biblebrainringserverlib/server_classical/servermodegameabstract.h"

ServerModeGameAbstract::ServerModeGameAbstract(const ServerMode mode, const QString &objectName, QObject *parent) : ServerModeAbstract(mode, objectName, parent)
{

}

QVector<QString> ServerModeGameAbstract::getSparringTeams()
{
    QVector<QString> vec;
    for (const TeamDto &team : listTeams) {
        vec.append(team.guid);
    }
    return vec;
}

void ServerModeGameAbstract::sendToSparringTeams(const QString &method, const QJsonValue &params, const QJsonValue &id, const TeamStatus &status)
{
    QJsonObject obj;
    obj.insert(key_jsonrpc, value_jsonrpc);
    obj.insert(key_method, method);
    if (params != QJsonValue::Null) {
        obj.insert(key_params, params);
    }
    if (id != QJsonValue::Null) {
        obj.insert(key_id, id);
    }
    const QByteArray arr = QJsonDocument(obj).toJson();
    for (const TeamDto &team : qAsConst(vecSparringTeams)) {
        if (team.status == status) {
            io->sendToClient(team.guid, arr, 5000);
        }
    }
}
