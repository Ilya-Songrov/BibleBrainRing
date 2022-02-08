#pragma once

#include <QObject>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QFileInfo>
#include <QDir>

#include "state_machine/all_states.h"

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
    void changeAppState(StateAbstract *state);
    void setConnections();

private:
    StateAbstract *currentState;
};

