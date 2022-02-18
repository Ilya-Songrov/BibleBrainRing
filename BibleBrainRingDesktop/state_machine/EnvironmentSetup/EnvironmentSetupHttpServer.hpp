#pragma once

#include <QNetworkInterface>

#include "EnvironmentSetup.hpp"

class EnvironmentSetupHttpServer : public EnvironmentSetup
{
public:
    explicit EnvironmentSetupHttpServer(QObject *parent = nullptr);

    virtual StateAbstract *onQmlButtonClicked   (const BibleBrainRing::Button button) ;

private:
    void runCustomServer();
};

