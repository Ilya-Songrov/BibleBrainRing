#pragma once

#include <QObject>
#include <QJsonDocument>

#include "global_enums.h"
#include "global_utils.h"

class StateAbstract : public QObject
{
    Q_OBJECT
public:
    explicit StateAbstract(const QString &objectName, QObject *parent = nullptr);

    virtual StateAbstract *onEndQmlCreation     ();
    virtual StateAbstract *onQmlButtonClicked   (const BibleBrainRing::Button button);

protected:
    void printCurrentState();
};

