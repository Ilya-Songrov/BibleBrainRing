#pragma once

#include "StateAbstract.h"
#include "all_states.h"

class EnvironmentSetup : public StateAbstract
{
public:
    explicit EnvironmentSetup(QObject *parent = nullptr);

    virtual StateAbstract *onQmlButtonClicked   (const BibleBrainRing::Button button) override;
};

