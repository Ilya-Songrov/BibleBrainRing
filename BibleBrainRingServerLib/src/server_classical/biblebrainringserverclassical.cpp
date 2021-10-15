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

#include "biblebrainringserverlib/server_classical/biblebrainringserverclassical.h"

BibleBrainRingServerClassical::BibleBrainRingServerClassical(IODeviceServerAbstract *ioDeviceServerAbstract)
    : currentServerMode(nullptr)
{
    connect(ioDeviceServerAbstract, &IODeviceServerAbstract::joinedClient,          this,
            [this](const QString &guidClient){ currentServerMode->slotJoinedClient(guidClient); });
    connect(ioDeviceServerAbstract, &IODeviceServerAbstract::responseFromClient,    this,
            [this](const QString &guidClient, const QByteArray &arr){ currentServerMode->slotResponseFromClient(guidClient, arr); });
    connect(ioDeviceServerAbstract, &IODeviceServerAbstract::clientStatusChanged,   this,
            [this](const QString &guidClient, const IODeviceServerAbstract::ClientStatus clientStatus){ currentServerMode->slotClientStatusChanged(guidClient, clientStatus); });
    connect(ioDeviceServerAbstract, &IODeviceServerAbstract::serverStatusChanged,   this,
            [](const QString &status){ qDebug() << status << Qt::endl; });

    changeCurrentServerMode(new ServerModeInitialization(ioDeviceServerAbstract));
}

BibleBrainRingServerClassical::~BibleBrainRingServerClassical()
{

}

bool BibleBrainRingServerClassical::initServer()
{
    ServerModeAbstract* mode = currentServerMode->initServer();
    changeCurrentServerMode(mode);
    return mode != nullptr;
}

ServerMode BibleBrainRingServerClassical::getCurrentServerMode()
{
    if (currentServerMode) {
        return currentServerMode->getCurrentServerMode();
    }
    return ServerMode::Unknown;
}

void BibleBrainRingServerClassical::startRegistration()
{
    ServerModeAbstract* mode = currentServerMode->startRegistration();
    changeCurrentServerMode(mode);
}

void BibleBrainRingServerClassical::stopRegistration()
{
    ServerModeAbstract* mode = currentServerMode->stopRegistration();
    changeCurrentServerMode(mode);
}

void BibleBrainRingServerClassical::setSparringTeams(const QVector<QString> &vecGuidTeam)
{
    ServerModeAbstract* mode = currentServerMode->setSparringTeams(vecGuidTeam);
    changeCurrentServerMode(mode);
}

QVector<QString> BibleBrainRingServerClassical::getSparringTeams()
{
    return currentServerMode->getSparringTeams();
}

void BibleBrainRingServerClassical::activateButtonsSparringTeams()
{
    ServerModeAbstract* mode = currentServerMode->activateButtonsSparringTeams();
    changeCurrentServerMode(mode);
}

void BibleBrainRingServerClassical::banTeam(const QString &guidTeam)
{
    ServerModeAbstract* mode = currentServerMode->banTeam(guidTeam);
    changeCurrentServerMode(mode);
}

TeamStatus BibleBrainRingServerClassical::getTeamStatus(const QString &guidTeam)
{
    return currentServerMode->getTeamStatus(guidTeam);;
}

void BibleBrainRingServerClassical::changeTeamScore(const QString &guidTeam, const double score)
{
    ServerModeAbstract* mode = currentServerMode->changeTeamScore(guidTeam, score);
    changeCurrentServerMode(mode);
}

int BibleBrainRingServerClassical::getTeamScore(const QString &guidTeam)
{
    return currentServerMode->getTeamScore(guidTeam);;
}

void BibleBrainRingServerClassical::laodListQuestions(const QStringList &questions)
{
    ServerModeAbstract* mode = currentServerMode->loadListQuestions(questions);
    changeCurrentServerMode(mode);
}

void BibleBrainRingServerClassical::changeQuestionStatus(const QString &question, const QuestionStatus questionStatus)
{
    ServerModeAbstract* mode = currentServerMode->changeQuestionStatus(question, questionStatus);
    changeCurrentServerMode(mode);
}

void BibleBrainRingServerClassical::finishRound()
{

}

void BibleBrainRingServerClassical::addRoundNote()
{

}

QString BibleBrainRingServerClassical::getRoundResult()
{

}

void BibleBrainRingServerClassical::onConnectNewTeam(std::function<void (const TeamDto &)> function)
{
    ServerModeAbstract::onConnectNewTeam(function);
}

void BibleBrainRingServerClassical::onTeamDtoChanged(std::function<void (const TeamDto &)> function)
{
    ServerModeAbstract::onTeamDtoChanged(function);
}

void BibleBrainRingServerClassical::changeCurrentServerMode(ServerModeAbstract *mode)
{
    if (mode) {
        delete currentServerMode;
        currentServerMode = mode;
    }
}

