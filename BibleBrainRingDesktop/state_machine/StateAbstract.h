#pragma once

#include <QObject>
#include <QJsonDocument>
#include <QInputDialog>

#include "global_enums.h"
#include "global_utils.h"
#include "ListTeams.hpp"
#include "ListScreens.hpp"
#include "ManagerQuestions.hpp"

class StateAbstract : public QObject
{
    Q_OBJECT
public:
    explicit StateAbstract(const QString &objectName, QObject *parent = nullptr);

    virtual StateAbstract *onEndQmlCreation     ();
    virtual StateAbstract *onQmlButtonClicked   (const BibleBrainRing::Button button);

protected:
    void printCurrentState();

protected:
    static QScopedPointer<ListTeams> listTeamsRegistration;
    static QScopedPointer<ListTeams> listTeamsInGameSession;
    static QScopedPointer<ListTeams> listTeamsInBattle;
    static QScopedPointer<ListTeams> listTeamsInResult;
    static QScopedPointer<ListScreens> listScreens;
    static QScopedPointer<ManagerQuestions> managerQuestions;
};

