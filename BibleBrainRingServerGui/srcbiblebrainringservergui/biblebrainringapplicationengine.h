#pragma once

#include <QObject>
#include <QQmlApplicationEngine>
#include <QQmlContext>

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
};

