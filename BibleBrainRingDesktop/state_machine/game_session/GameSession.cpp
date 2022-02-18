#include "GameSession.hpp"

GameSession::GameSession(QObject *parent)
    : StateAbstract(__FUNCTION__, parent)
    , refereeStartTime(QDateTime::currentSecsSinceEpoch())
{
    setConnections();
    loadTeams();
    settingTimer();
    providerQml->setCurrentAppState(BibleBrainRing::GameSession);
    providerQml->setVisibleBulbOnScreen(false);
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
    if (!timerFroShowingResult.isActive()) {
        timerFroShowingResult.start();
    }
    else if(vecButtonPressed.size() == listTeamsInBattle->getListSize()){
        showResult();
        timerFroShowingResult.stop();
    }
}

void GameSession::slotRefereeReset(qint64)
{
    for (const TeamDto& team: qAsConst(listTeamsInBattle->getList())) {
        listTeamsInBattle->setBulbPosition(0, team.guid);
    }
    vecButtonPressed.clear();
    timerFroShowingResult.stop();
    providerQml->setVisibleBulbOnScreen(false);
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

void GameSession::settingTimer()
{
    connect(&timerFroShowingResult, &QTimer::timeout, this, &GameSession::showResult);
    timerFroShowingResult.setInterval(3000);
}

void GameSession::showResult()
{
//    QList<TeamDto> listSortInBattle = listTeamsInBattle->getList();
//    std::sort(listSortInBattle.begin(), listSortInBattle.end(), [](const TeamDto& t1, const TeamDto& t2){ return t1.bulbPosition < t2.bulbPosition; });
//    if (!listSortInBattle.isEmpty()) {
//        int step = 0;
//        for (const TeamDto& teamVoted : listSortInBattle) {
//            for (const TeamDto& team: qAsConst(listTeamsInBattle->getList())) {
//                if (teamVoted.guid == team.guid) {
//                    listTeamsInBattle->setBulbPosition(++step, team.guid);
//                }
//            }
//        }
//    }
    QVector<DtoButtonPressedRq> vecSort = vecButtonPressed;
    std::sort(vecSort .begin(), vecSort .end(), [](const DtoButtonPressedRq& rq1, const DtoButtonPressedRq& rq2){ return rq1.time < rq2.time; });
    if (!vecSort .isEmpty()) {
        int step = 0;
        for (const DtoButtonPressedRq& rqVoted : vecSort ) {
            for (const TeamDto& team: qAsConst(listTeamsInBattle->getList())) {
                if (rqVoted.guid == team.guid) {
                    listTeamsInBattle->setBulbPosition(++step, team.guid);
                }
            }
        }
    }
    providerQml->setVisibleBulbOnScreen(true);
}
