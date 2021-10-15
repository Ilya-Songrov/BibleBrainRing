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

#include <QJsonDocument>
#include <QJsonObject>

#include "servermodeabstract.h"
#include "all_server_modes.h"
#include "biblebrainringserverlib/iodevice/iodeviceserverabstract.h"

class BibleBrainRingServerClassical : public QObject
{
    Q_OBJECT
public:
    explicit BibleBrainRingServerClassical(IODeviceServerAbstract *ioDeviceServerAbstract);
    ~BibleBrainRingServerClassical();

    bool initServer();
    ServerMode getCurrentServerMode();

    void startRegistration();
    void stopRegistration();

    void setSparringTeams(const QVector<QString>& vecGuidTeam);
    QVector<QString> getSparringTeams();
    void activateButtonsSparringTeams();

    void banTeam(const QString &guidTeam);
    TeamStatus getTeamStatus(const QString &guidTeam);

    void changeTeamScore(const QString &guidTeam, const double score);
    int getTeamScore(const QString &guidTeam);

    void laodListQuestions(const QStringList &questions);
    void changeQuestionStatus(const QString &question, const QuestionStatus questionStatus);

    void finishRound();
    void addRoundNote();
    QString getRoundResult();

    // callbacks:
    void onConnectNewTeam   (std::function<void(const TeamDto &)> function);
    void onTeamDtoChanged   (std::function<void(const TeamDto &)> function);

private:
    void changeCurrentServerMode(ServerModeAbstract *mode);

private:
    ServerModeAbstract* currentServerMode;
};

