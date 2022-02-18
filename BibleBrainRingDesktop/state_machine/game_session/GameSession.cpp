#include "GameSession.hpp"

GameSession::GameSession(QObject *parent)
    : StateAbstract(__FUNCTION__, parent)
    , refereeStartTime(0)
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
    if(vecButtonPressed.size() == listTeamsInBattle->getListSize()){
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
    refereeStartTime = 0;
    bulbPowerForAll(false);
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
    connect(providerQml.get(), &ProviderQml::resetBulbScore, this, &GameSession::slotRefereeReset);
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
    QVector<DtoButtonPressedRq> vecSort = vecButtonPressed;
    std::sort(vecSort .begin(), vecSort .end(), [](const DtoButtonPressedRq& rq1, const DtoButtonPressedRq& rq2){ return rq1.time < rq2.time; });
    if (!vecSort .isEmpty()) {
        int step = 0;
        for (const DtoButtonPressedRq& rqVoted : vecSort ) {
            for (const TeamDto& team: qAsConst(listTeamsInBattle->getList())) {
                if (rqVoted.guid == team.guid) {
                    int currentStep = ++step;
                    if (providerQml->getUseReferee()) {
                        currentStep = refereeStartTime > rqVoted.time ? currentStep * -1 : currentStep;
                    }
                    listTeamsInBattle->setBulbPosition(currentStep, team.guid);
                    if (step == 0) {
                        setBulbPower(listTeamsInBattle->getIndex(team.guid), true);
                    }
                }
            }
        }
    }
    providerQml->setVisibleBulbOnScreen(true);
}

void GameSession::setBulbPower(const int index, const bool power)
{
    if (index > -1 && vecBulbs.size() < index) {
        vecBulbs.at(index)->set_power(power, YeelightBulb::Bulb::Sudden, 1);
    }
    else{
        qWarning() << "print_function:" << __FUNCTION__ << __LINE__ << " index is invalid: " << index << Qt::endl;
    }
}

void GameSession::bulbPowerForAll(const bool power,
                                  const YeelightBulb::Bulb::BulbEffect bulbEffect,
                                  const int duration)
{
    for (YeelightBulb::Bulb* bulb: qAsConst(vecBulbs)) {
        bulb->set_power(power, bulbEffect, duration);
    }
}
