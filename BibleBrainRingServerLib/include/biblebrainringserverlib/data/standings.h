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

#include <QDebug>
#include <QVector>

#include "biblebrainringserverlib/dtos/teamdto.h"

class Standings
{
public:
    explicit Standings();

    void clearStandings();

    void openRound(const QVector<TeamDto> &vecTeams);
    void closeRound();

    void setScoreInCurrentRound(const TeamDto &team, const double score);
    double getScoreInCurrentRound(const TeamDto &team);

private:
    struct Round{
        const TeamDto player                ;
        double score                  = TeamDto{}.score;
        Round(const TeamDto &t, const double s) : player(t), score(s) {}
    };
    struct Sparring{
        const TeamDto player                ;
        const QVector<TeamDto> opponents    ;
        const double score                  = TeamDto{}.score;
        Sparring(const TeamDto &t, QVector<TeamDto> o, const double s) : player(t), opponents(o), score(s) {}
    };
    QVector<Sparring> vecSparrings;
    QVector<Round> vecCurrenRound;
};

