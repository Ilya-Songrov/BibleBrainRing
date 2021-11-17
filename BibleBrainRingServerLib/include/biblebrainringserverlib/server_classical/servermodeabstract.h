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

#include <QObject>

#include "biblebrainringserverlib/iodevice/iodeviceserverabstract.h"
#include "biblebrainringserverlib/dtos/dtocreator.h"
#include "biblebrainringserverlib/data/questions.h"
#include "biblebrainringserverlib/data/standings.h"
#include "biblebrainringserverlib/information/informationconsoleprinter.h"

class ServerModeAbstract : public QObject
{
    Q_OBJECT
public:
    explicit ServerModeAbstract(const ServerMode mode, const QString &objectName, QObject *parent = nullptr);

    virtual ServerModeAbstract* initServer();

    virtual ServerModeAbstract* startRegistration();
    virtual ServerModeAbstract* stopRegistration();

    virtual ServerModeAbstract* banTeam(const QString &guidTeam);
    virtual ServerModeAbstract* setSparringTeams(const QVector<QString>& vecGuidTeam);

    virtual ServerModeAbstract* activateButtonsSparringTeams();
    virtual ServerModeAbstract* deactivateButtonsSparringTeams();

    virtual ServerModeAbstract* startRound(const int timeoutMsecs);
    virtual ServerModeAbstract* finishSparring();
    virtual ServerModeAbstract* addSparringNote(const QString &note);
    virtual ServerModeAbstract* changeTeamScore(const QString &guidTeam, const double score);

    virtual ServerModeAbstract* loadListQuestions(const QStringList &questions);
    virtual ServerModeAbstract* changeQuestionStatus(const QString &question, const QuestionStatus questionStatus);

    virtual ServerModeAbstract* slotJoinedClient(const QString &guidClient);
    virtual ServerModeAbstract* slotResponseFromClient(const QString &guidClient, const QByteArray &arrBytes);
    virtual ServerModeAbstract* slotClientStatusChanged(const QString &guidClient, const IODeviceServerAbstract::ClientStatus clientStatus);

    virtual TeamStatus getTeamStatus(const QString &guidTeam);
    virtual QVector<QString> getSparringTeams();
    virtual QString getRoundResult();
    virtual QString getSparringResult();
    virtual int getTeamScore(const QString &guidTeam);

    ServerMode getCurrentServerMode();

    static void onConnectNewTeam   (std::function<void(const TeamDto &)> function);
    static void onTeamDtoChanged   (std::function<void(const TeamDto &)> function);

protected:
    void changeTeam(const TeamDto &team, const bool runCallback = false);
    TeamDto getTeam(const QString &guidTeam);

    void bunTeam(const QString &guidTeam);
    void changeClientStatus(const QString &guidClient, const IODeviceServerAbstract::ClientStatus clientStatus);


protected:
    static IODeviceServerAbstract* io;
    static Questions q;
    static Standings s;
    static QList<TeamDto> listTeams;
    static std::function<void(const TeamDto &)>    functionConnectNewTeam;
    static std::function<void(const TeamDto &)>    functionTeamDtoChanged;

    static const QString print_color;
    static const QString key_jsonrpc;
    static const QString key_method;
    static const QString key_params;
    static const QString key_result;
    static const QString key_id;
    static const QString value_jsonrpc;

private:
    ServerMode _mode;

};

