#include "GameSession.hpp"

GameSession::GameSession(QObject *parent)
    : StateAbstract(__FUNCTION__, parent)
{
    setConnections();
    loadTeams();
    providerQml->setCurrentAppState(BibleBrainRing::GameSession);

#ifdef QT_DEBUG
//    managerQuestions->loadQuestions("/home/songrov/test_questions.txt");
    TeamDto team;
    team.guid        = "guid";
    team.name        = "name";
    team.color       = "green";
    team.score       = 2;
    team.position    = 3;
    team.status      = TeamStatus::Registered;
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

void GameSession::setConnections()
{
    connect(listTeamsInGameSession.get(), &ListTeams::moveTeamToAnotherList, this, [](int index){
        const TeamDto team = listTeamsInGameSession->getTeam(index);
        listTeamsInBattle->appendTeam(team);
        listTeamsInGameSession->removeTeam(index);
    });
    connect(listTeamsInBattle.get(), &ListTeams::moveTeamToAnotherList, this, [](int index){
        const TeamDto team = listTeamsInBattle->getTeam(index);
        listTeamsInGameSession->appendTeam(team);
        listTeamsInBattle->removeTeam(index);
    });
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
    for (const TeamDto& teamG: qAsConst(listTeamsInGameSession->getList())) {
        bool found = false;
        for (const TeamDto& teamR: qAsConst(listTeamsInResult->getList())) {
            if (teamG.name == teamR.name) {
                found = true;
                break;
            }
        }
        if (!found) {
            listTeamsInResult->appendTeam(teamG);
        }
    }
}
