#include "GameSession.hpp"

GameSession::GameSession(QObject *parent)
    : StateAbstract(__FUNCTION__, parent)
    , refereeStartTime(QDateTime::currentSecsSinceEpoch())
{
    setConnections();
    loadTeams();
    providerQml->setCurrentAppState(BibleBrainRing::GameSession);


#ifdef QT_DEBUG
//    managerQuestions->loadQuestions("/home/songrov/test_questions.txt");
//    TeamDto team;
//    team.guid        = "guid";
//    team.name        = "name";
//    team.color       = "green";
//    team.score       = 2;
//    team.position    = 3;
//    team.bulbPosition= 1;
//    team.status      = TeamStatus::Registered;
//    listTeamsInBattle->appendTeam(team);
//    team.color      = "blue";
//    team.status     = TeamStatus::Registered;
//    team.name       = "name nameA nameA nameA";
//    team.guid       = "1111";
//    listTeamsInBattle->appendTeam(team);
//    team.name       = "name nameB nameB nameB";
//    team.guid       = "2222";
//    listTeamsInGameSession->appendTeam(team);
//    listTeamsInGameSession->appendTeam(team);
//    listTeamsInGameSession->appendTeam(team);
//    listTeamsInGameSession->appendTeam(team);
//    listTeamsInGameSession->appendTeam(team);
//    listTeamsInGameSession->appendTeam(team);
//    listTeamsInGameSession->appendTeam(team);
//    listTeamsInGameSession->appendTeam(team);
//    listTeamsInGameSession->appendTeam(team);
//    listTeamsInGameSession->appendTeam(team);
//    listTeamsInGameSession->appendTeam(team);
//    listTeamsInGameSession->appendTeam(team);
//    listTeamsInGameSession->appendTeam(team);
//    listTeamsInGameSession->appendTeam(team);
//    listTeamsInGameSession->appendTeam(team);
//    listTeamsInGameSession->appendTeam(team);
//    listTeamsInGameSession->appendTeam(team);
#endif
}

StateAbstract* GameSession::onQmlButtonClicked(const BibleBrainRing::Button button)
{
    if (button == BibleBrainRing::ButtonComeback) {
        return new RegistrationStateMain();
    }
    else if (button == BibleBrainRing::ButtonNext) {
        return new ShowingResult();
    }
    return nullptr;
}

void GameSession::slotPressedButtonBulb(DtoButtonPressedRq rq)
{
    qDebug() << "print_function:" << __FUNCTION__ << "guid:" << rq.guid << "time:" << rq.time << Qt::endl;
    for (const DtoButtonPressedRq& rqSaved: qAsConst(vecButtonPressed)) {
        if (rqSaved.guid == rq.guid) {
            return;
        }
    }
    vecButtonPressed.append(rq);
    for (const TeamDto& team: qAsConst(listTeamsInBattle->getList())) {
        if (team.guid == rq.guid) {
            listTeamsInBattle->setBulbPosition(vecButtonPressed.size(), team.guid);
        }
    }
}

void GameSession::slotRefereeReset(qint64)
{
    for (const DtoButtonPressedRq& rq: qAsConst(vecButtonPressed)) {
        listTeamsInBattle->setBulbPosition(0, rq.guid);
    }
    vecButtonPressed.clear();
}

void GameSession::slotRefereeStartTime(qint64 time)
{
    refereeStartTime = time;
}

void GameSession::setConnections()
{
    connect(listTeamsInGameSession.get(), &ListTeams::moveTeamToAnotherList, this, [](int index){
        const TeamDto team = listTeamsInGameSession->getTeam(index);
        listTeamsInBattle->appendTeam(team);
        listTeamsInGameSession->removeTeam(index);
        bibleBrainRingServerClassical->changeTeamStatus(team.guid, TeamStatus::InBattle);
    });
    connect(listTeamsInBattle.get(), &ListTeams::moveTeamToAnotherList, this, [](int index){
        const TeamDto team = listTeamsInBattle->getTeam(index);
        listTeamsInGameSession->appendTeam(team);
        listTeamsInBattle->removeTeam(index);
        bibleBrainRingServerClassical->changeTeamStatus(team.guid, TeamStatus::WaitingForTheNextRound);
    });
    connect(bibleBrainRingServerClassical.get(), &BibleBrainRingServerClassical::signalPressedButton,
            this, &GameSession::slotPressedButtonBulb, Qt::BlockingQueuedConnection);
    connect(bibleBrainRingServerClassical.get(), &BibleBrainRingServerClassical::signalRefereeReset,
            this, &GameSession::slotRefereeReset, Qt::BlockingQueuedConnection);
    connect(bibleBrainRingServerClassical.get(), &BibleBrainRingServerClassical::signalRefereeStartTime,
            this, &GameSession::slotRefereeStartTime, Qt::BlockingQueuedConnection);
}

void GameSession::loadTeams()
{
    listTeamsInBattle->clear();
    listTeamsInGameSession->clear();
    for (const TeamDto& team: qAsConst(listTeamsRegistration->getList())) {
        if (team.status == Registered || team.status == WaitingForTheNextRound || team.status == InBattle) {
            listTeamsInGameSession->appendTeam(team);
        }
    }
}
