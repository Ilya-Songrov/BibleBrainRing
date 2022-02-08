#include "GameSession.hpp"

GameSession::GameSession(QObject *parent)
    : StateAbstract(__FUNCTION__, parent)
{
    setConnections();
    providerQml->setCurrentAppState(BibleBrainRing::GameSession);

    TeamDto team;
    team.guid        = "guid";
    team.name        = "name";
    team.color       = "green";
    team.score       = 2;
    team.position    = 3;
    team.status      = TeamStatus::Registered;
    listTeamsInGameSession->appendTeam(team);
    team.color      = "blue";
    team.status      = TeamStatus::Registered;
    team.name = "name 1111";
    team.guid = "1111";
    listTeamsInGameSession->appendTeam(team);
    team.name = "name 2222";
    team.guid = "2222";
    listTeamsInGameSession->appendTeam(team);
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
