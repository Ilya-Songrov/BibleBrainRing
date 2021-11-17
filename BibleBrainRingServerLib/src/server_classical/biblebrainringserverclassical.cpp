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
    : _currentServerMode(nullptr)
    , _ioDeviceServerAbstract(ioDeviceServerAbstract)
{
    connect(_ioDeviceServerAbstract, &IODeviceServerAbstract::joinedClient,          this,
            [this](const QString &guidClient){ _currentServerMode->slotJoinedClient(guidClient); });
    connect(_ioDeviceServerAbstract, &IODeviceServerAbstract::responseFromClient,    this,
            [this](const QString &guidClient, const QByteArray &arr){ _currentServerMode->slotResponseFromClient(guidClient, arr); });
    connect(_ioDeviceServerAbstract, &IODeviceServerAbstract::clientStatusChanged,   this,
            [this](const QString &guidClient, const IODeviceServerAbstract::ClientStatus clientStatus){ _currentServerMode->slotClientStatusChanged(guidClient, clientStatus); });
    connect(_ioDeviceServerAbstract, &IODeviceServerAbstract::serverStatusChanged,   this,
            [](const QString &status){ qDebug() << status << Qt::endl; });

    changeCurrentServerMode(new ServerModeInitialization(_ioDeviceServerAbstract));
}

BibleBrainRingServerClassical::~BibleBrainRingServerClassical()
{

}

bool BibleBrainRingServerClassical::initServer()
{
    ServerModeAbstract* mode = _currentServerMode->initServer();
    changeCurrentServerMode(mode);
    return mode != nullptr;
}

void BibleBrainRingServerClassical::setCurrentServerMode(const ServerMode serverMode)
{
    ServerModeAbstract* mode = nullptr;
    if (serverMode == Unknown) {
        qWarning() << "It is a bad idea. I ignored your request" << Qt::endl;
        return;
    }
    else if (serverMode == Initialization) {
        mode = new ServerModeInitialization(_ioDeviceServerAbstract);
    }
    else if (serverMode == Idle) {
        mode = new ServerModeIdle();
    }
    else if (serverMode == AcceptsRegistrations) {
        mode = new ServerModeAcceptsRegistrations();
    }
    else if (serverMode == SelectingSparringTeams) {
        mode = new ServerModeSelectingSparringTeams();
    }
    else if (serverMode == RunningSparring) {
        mode = new ServerModeRunningSparring();
    }
    else if (serverMode == ShowingSparringResult) {
        mode = new ServerModeShowingSparringResult();
    }
    else if (serverMode == ShowingGameResult) {
        mode = new ServerModeShowingGameResult();
    }
    changeCurrentServerMode(mode);
}

ServerMode BibleBrainRingServerClassical::getCurrentServerMode()
{
    if (_currentServerMode) {
        return _currentServerMode->getCurrentServerMode();
    }
    return ServerMode::Unknown;
}

void BibleBrainRingServerClassical::startRegistration()
{
    ServerModeAbstract* mode = _currentServerMode->startRegistration();
    changeCurrentServerMode(mode);
}

void BibleBrainRingServerClassical::stopRegistration()
{
    ServerModeAbstract* mode = _currentServerMode->stopRegistration();
    changeCurrentServerMode(mode);
}

void BibleBrainRingServerClassical::banTeam(const QString &guidTeam)
{
    ServerModeAbstract* mode = _currentServerMode->banTeam(guidTeam);
    changeCurrentServerMode(mode);
}

TeamStatus BibleBrainRingServerClassical::getTeamStatus(const QString &guidTeam)
{
    return _currentServerMode->getTeamStatus(guidTeam);;
}

void BibleBrainRingServerClassical::setSparringTeams(const QVector<QString> &vecGuidTeam)
{
    ServerModeAbstract* mode = _currentServerMode->setSparringTeams(vecGuidTeam);
    changeCurrentServerMode(mode);
}

QVector<QString> BibleBrainRingServerClassical::getSparringTeams()
{
    return _currentServerMode->getSparringTeams();
}

void BibleBrainRingServerClassical::activateButtonsSparringTeams()
{
    ServerModeAbstract* mode = _currentServerMode->activateButtonsSparringTeams();
    changeCurrentServerMode(mode);
}

void BibleBrainRingServerClassical::deactivateButtonsSparringTeams()
{
    ServerModeAbstract* mode = _currentServerMode->deactivateButtonsSparringTeams();
    changeCurrentServerMode(mode);
}

void BibleBrainRingServerClassical::startRound(const int timeoutMsecs)
{

}

void BibleBrainRingServerClassical::finishSparring()
{

}

void BibleBrainRingServerClassical::addSparringNote(const QString &note)
{

}

QString BibleBrainRingServerClassical::getRoundResult()
{

}

QString BibleBrainRingServerClassical::getSparringResult()
{

}

void BibleBrainRingServerClassical::changeTeamScore(const QString &guidTeam, const double score)
{
    ServerModeAbstract* mode = _currentServerMode->changeTeamScore(guidTeam, score);
    changeCurrentServerMode(mode);
}

int BibleBrainRingServerClassical::getTeamScore(const QString &guidTeam)
{
    return _currentServerMode->getTeamScore(guidTeam);;
}

void BibleBrainRingServerClassical::laodListQuestions(const QStringList &questions)
{
    ServerModeAbstract* mode = _currentServerMode->loadListQuestions(questions);
    changeCurrentServerMode(mode);
}

void BibleBrainRingServerClassical::changeQuestionStatus(const QString &question, const QuestionStatus questionStatus)
{
    ServerModeAbstract* mode = _currentServerMode->changeQuestionStatus(question, questionStatus);
    changeCurrentServerMode(mode);
}

void BibleBrainRingServerClassical::setCurrentQuestion(const QString &question)
{

}

QString BibleBrainRingServerClassical::getCurrentQuestion()
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
        delete _currentServerMode;
        _currentServerMode = mode;
    }
}

