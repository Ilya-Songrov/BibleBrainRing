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

#include "dtoabstract.h"
#include "enums/global_enums.h"

struct TeamDto : public DtoAbstract
{
    QString guid        ;
    QString name        ;
    QString color       ;
    double score        = -1.0;
    int position        = -1;
    TeamStatus status   = TeamStatus::None;
};
