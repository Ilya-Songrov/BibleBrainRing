#pragma once

#include <QMessageBox>

#include "StateAbstract.h"

class EnvironmentSetup : public StateAbstract
{
public:
    explicit EnvironmentSetup(const QString &objectName, QObject *parent = nullptr);

    virtual StateAbstract *onQmlButtonClicked   (const BibleBrainRing::Button button) override;

protected:
    QString getListNetwork();

private:
    void addBulb();
};

