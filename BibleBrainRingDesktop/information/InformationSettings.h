#pragma once

#include <QObject>
#include <QGuiApplication>
#include <QScreen>
#include <QNetworkInterface>

#include "InformationAbstract.h"


class InformationSettings : public InformationAbstract
{
public:
    explicit InformationSettings();

    static void initValues();

    static const QRect &getRectPrimaryScreen();

private:
    static inline void initRectPrimaryScreen();

private:
    static QRect        rectPrimaryScreen;
};

