#include "ShowingResult.hpp"

ShowingResult::ShowingResult(QObject *parent)
    : StateAbstract(__FUNCTION__, parent)
{
    providerQml->setCurrentAppState(BibleBrainRing::ShowingResult);
    updateScores();
}

StateAbstract* ShowingResult::onQmlButtonClicked(const BibleBrainRing::Button button)
{
    if (button == BibleBrainRing::ButtonComeback) {
        return new GameSession();
    }
    else if (button == BibleBrainRing::ButtonNext) {
        const int res = QMessageBox::question(nullptr, QObject::tr("Game"), "Do you want to end the game and lose all progress?");
        if (res == QMessageBox::Button::Yes) {
            return new StartStateMenuMain();
        }
    }
    return nullptr;
}

void ShowingResult::updateScores()
{
    for (TeamDto& teamR: listTeamsInResult->getList()) {
        for (const TeamDto& teamB: qAsConst(listTeamsInBattle->getList())) {
            if (teamR.name == teamB.name) {
                teamR.score += teamB.score;
                emit listTeamsInResult->updateModel();
                break;
            }
        }
    }
}
