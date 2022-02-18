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

private:
    qint64 refereeStartTime;
    QVector<DtoButtonPressedRq> vecButtonPressed;
};

