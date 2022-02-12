#pragma once

#include "StateAbstract.h"
#include "all_states.h"

class ShowingResult : public StateAbstract
{
public:
    explicit ShowingResult(QObject *parent = nullptr);

    virtual StateAbstract *onQmlButtonClicked   (const BibleBrainRing::Button button) override;

private:
    void updateScores();
};

