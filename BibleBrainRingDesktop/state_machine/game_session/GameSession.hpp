#pragma once

#include "StateAbstract.h"
#include "all_states.h"

class GameSession : public StateAbstract
{
public:
    explicit GameSession(QObject *parent = nullptr);

    virtual StateAbstract *onQmlButtonClicked   (const BibleBrainRing::Button button) override;

private:
    void setConnections();
};

