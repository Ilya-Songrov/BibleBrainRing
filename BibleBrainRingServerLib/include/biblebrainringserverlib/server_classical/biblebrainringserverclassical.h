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

    void setCurrentServerMode(const ServerMode serverMode);
    ServerMode getCurrentServerMode();

    void startRegistration();
    void stopRegistration();

    void banTeam(const QString &guidTeam);
    TeamStatus getTeamStatus(const QString &guidTeam);

    void setSparringTeams(const QVector<QString>& vecGuidTeam);
    QVector<QString> getSparringTeams();

    void activateButtonsSparringTeams();
    void deactivateButtonsSparringTeams();

    void startRound(const int timeoutMsecs);
    void finishSparring();
    void addSparringNote(const QString &note);
    QString getRoundResult();
    QString getSparringResult();

    void changeTeamScore(const QString &guidTeam, const double score);
    int getTeamScore(const QString &guidTeam);

    void laodListQuestions(const QStringList &questions);
    void changeQuestionStatus(const QString &question, const QuestionStatus questionStatus);
    void setCurrentQuestion(const QString &question);
    QString getCurrentQuestion();


    // callbacks:
    void onConnectNewTeam   (std::function<void(const TeamDto &)> function);
    void onTeamDtoChanged   (std::function<void(const TeamDto &)> function);

private:
    void changeCurrentServerMode(ServerModeAbstract *mode);

private:
    ServerModeAbstract* _currentServerMode;
    IODeviceServerAbstract *_ioDeviceServerAbstract;
};

