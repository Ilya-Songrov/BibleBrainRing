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

#include "dtos/dtocreator.h"

TeamDto DtoCreator::getTeamDto(const QString &guid, const QString &name, const QString &color, const double score, const int position, const TeamStatus status)
{
    TeamDto team;
    team.guid        = guid;
    team.name        = name;
    team.color       = color;
    team.score       = score;
    team.position    = position;
    team.status      = status;
    return team;
}

TeamDto DtoCreator::getTeamDto(const QString &guid, const TeamStatus status)
{
    return DtoCreator::getTeamDto(guid, {}, {}, TeamDto{}.score, TeamDto{}.position, status);
}

TeamDto DtoCreator::getTeamDto(const QJsonObject &obj)
{
    TeamDto team;
    team.guid        = obj.value("guid")      .toString();
    team.name        = obj.value("name")      .toString();
    team.color       = obj.value("color")     .toString();
    team.score       = obj.value("score")     .toDouble();
    team.position    = obj.value("position")  .toInt();
    team.status      = (TeamStatus)obj.value("status")    .toInt();
    return team;
}
