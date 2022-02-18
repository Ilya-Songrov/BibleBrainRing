#pragma once

#include "StateAbstract.h"
#include "all_states.h"

class GameSession : public StateAbstract
{
public:
    explicit GameSession(QObject *parent = nullptr);

    virtual StateAbstract *onQmlButtonClicked   (const BibleBrainRing::Button button) override;

private slots:
    void slotPressedButtonBulb(DtoButtonPressedRq rq);
    void slotRefereeReset(qint64);
    void slotRefereeStartTime(qint64 time);

private:
    void setConnections();
    void loadTeams();
    void settingTimer();
    void showResult();
    void setBulbPower(const int index, const bool power);
    void bulbPowerForAll(const bool power,
                         const YeelightBulb::Bulb::BulbEffect bulbEffect = YeelightBulb::Bulb::Sudden,
                         const int duration = 1);

private:
    qint64 refereeStartTime;
    QVector<DtoButtonPressedRq> vecButtonPressed;
    QTimer timerFroShowingResult;
};

