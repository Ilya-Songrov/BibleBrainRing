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

#include "biblebrainringserverlib/data/standings.h"

Standings::Standings()
{

}

void Standings::clearStandings()
{

}

void Standings::openRound(const QVector<TeamDto> &vecTeams)
{
    closeRound();
    const double defaultScore = TeamDto{}.score;
    for (const TeamDto &teamPlayer : vecTeams) {
        vecCurrenRound.append(Round{teamPlayer, defaultScore});
    }
}

void Standings::closeRound()
{
    for (const Round &roundPlayer : qAsConst(vecCurrenRound)) {
        QVector<TeamDto> opponents;
        for (const Round &roundOpponent : qAsConst(vecCurrenRound)) {
            if (roundPlayer.player.guid != roundOpponent.player.guid) {
                opponents.append(roundOpponent.player);
            }
        }
        vecSparrings.append(Sparring{roundPlayer.player, opponents, roundPlayer.score});
    }
    vecCurrenRound.clear();
}

void Standings::setScoreInCurrentRound(const TeamDto &team, const double score)
{
    for (Round &round: vecCurrenRound) {
        if (team.guid == round.player.guid) {
            round.score = score;
            return;
        }
    }
    qWarning() << "The current player is not in the standings" << Qt::endl;
}

double Standings::getScoreInCurrentRound(const TeamDto &team)
{
    for (Round &round: vecCurrenRound) {
        if (team.guid == round.player.guid) {
            return round.score;
        }
    }
    qWarning() << "The current player is not in the standings" << Qt::endl;
    return TeamDto{}.score;
}

