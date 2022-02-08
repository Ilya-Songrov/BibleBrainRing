#pragma once

#include <QObject>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QFileInfo>
#include <QDir>

#include "state_machine/all_states.h"
#include "biblebrainringserverlib/server_classical/biblebrainringserverclassical.h"
#include "biblebrainringserverlib/iodevice/tcp/tcpserver.h"

class BibleBrainRingApplicationEngine : public QQmlApplicationEngine
{
    Q_OBJECT
public:
    explicit BibleBrainRingApplicationEngine(QObject *parent = nullptr);
    ~BibleBrainRingApplicationEngine();


private:
    QScopedPointer<BibleBrainRingServerClassical> bbrClassical;
    StateAbstract *currentState;
};

