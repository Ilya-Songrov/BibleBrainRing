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

#include <QString>
#include <QJsonObject>

#include "../enums/global_enums.h"
#include "../dtos/teamdto.h"


class DtoCreator
{
public:
    static TeamDto getTeamDto(const QString &guid,
                           const QString &name = QString(),
                           const QString &color = QString(),
                           const double score = 0.0,
                           const int position = 0,
                           const TeamStatus status = TeamStatus::None);
    static TeamDto getTeamDto(const QString &guid,
                              const TeamStatus status);
    static TeamDto getTeamDto(const QJsonObject &obj);

};

