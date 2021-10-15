#pragma once

#include <QObject>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "stateabstract.h"
#include "all_states.h"
#include "global_utils.h"

class BibleBrainRingApplicationEngine : public QQmlApplicationEngine
{
    Q_OBJECT
public:
    explicit BibleBrainRingApplicationEngine(QObject *parent = nullptr);
    ~BibleBrainRingApplicationEngine();

private slots:
    void onEndQmlCreation();
    void onQmlButtonClicked(const BibleBrainRing::Button button);

private:
    void setConnections();
    void changeCurrentState(StateAbstract* state);

private:
    StateAbstract *currentState;
};

