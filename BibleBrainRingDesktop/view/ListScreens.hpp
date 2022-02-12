#pragma once

#include <QObject>
#include <QDebug>
#include <QGuiApplication>
#include <QScreen>

#include "AdditionalScreen.hpp"

class ListScreens : public QObject
{
    Q_OBJECT
public:
    explicit ListScreens(QObject *parent = nullptr);

    void initScreens();

    void appendScreen(const AdditionalScreen& screen);
    void appendScreens(const QList<QScreen *>& listScreens);
    void removeTeam(const int index);
    void clear();

    AdditionalScreen getScreen(const int index);
    QList<AdditionalScreen>& getList();
    int getListSize() const;

    void setScreenPrototype(const AdditionalScreen& screen);
    AdditionalScreen getScreenPrototype();

    Q_INVOKABLE QRect getRectForApp() const;
    Q_INVOKABLE QSize getSizeForBoundingItemScreenWidget() const;
    Q_INVOKABLE QSize getSizeForScreenWidget() const;

signals:
    void moveTeamToAnotherList(int index);

signals:
    void preResetModel      ();
    void postResetModel     ();
    void preSetItems        (const int count);
    void postSetItems       ();
    void preRemoveItems     (int first, int last);
    void postRemoveItems    ();
    void updateModel        ();

private:
    AdditionalScreen generateScreenPrototype();
    QRect generateRectForApp();
    QSize generateSizeForBoundingItemScreenWidget();

private:
    QList<AdditionalScreen> list;
    AdditionalScreen screenPrototype;
    QRect rectForApp;
    QSize sizeForBoundingItemScreenWidget;
    QSize sizeForScreenWidget;
};

