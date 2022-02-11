#pragma once

#include <QObject>
#include <QGuiApplication>
#include <QDesktopWidget>
#include <QScreen>
#include <QDebug>

class ManagerScreens : public QObject
{
    Q_OBJECT
public:
    explicit ManagerScreens(QObject *parent = nullptr);

    static QRect getRectPrimaryScreen();
    static QVariantList getInfoAdditionalScreens();
    static QSizeF getSizeForScreenWidget(const QSizeF boundingSize);
};

