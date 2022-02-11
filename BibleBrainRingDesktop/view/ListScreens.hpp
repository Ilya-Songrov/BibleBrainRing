#pragma once

#include <QObject>
#include <QDebug>

#include "AdditionalScreen.hpp"
#include "ManagerScreens.hpp"

class ListScreens : public QObject
{
    Q_OBJECT
public:
    explicit ListScreens(QObject *parent = nullptr);

    void appendTeam(const AdditionalScreen& screen);
    void removeTeam(const int index);
    void clear();

    AdditionalScreen getScreen(const int index);
    QList<AdditionalScreen>& getList();

    Q_INVOKABLE int getSize() const;

signals:
    void moveTeamToAnotherList(int index);

signals:
    void preResetModel      ();
    void postResetModel     ();
    void preSetItems        (const int count);
    void postSetItems       ();
    void preRemoveItems     (int first, int last);
    void postRemoveItems    ();

private:
    QList<AdditionalScreen> list;
    AdditionalScreen screenPrototype;
};

