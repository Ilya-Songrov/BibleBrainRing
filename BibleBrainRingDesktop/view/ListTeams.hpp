#pragma once

#include <QObject>
#include <QDebug>

#include "dtos/teamdto.h"

class ListTeams : public QObject
{
    Q_OBJECT
public:
    explicit ListTeams(QObject *parent = nullptr);

    void appendTeam(const TeamDto& team);
    void removeTeam(const TeamDto& team);
    void removeTeam(const int index);
    void clear();

    void setBulbPosition(const int bulbPosition, const QString& guidTeam);

    TeamDto getTeam(const int index);
    QList<TeamDto>& getList();

    Q_INVOKABLE int getListSize() const;
    Q_INVOKABLE void addTeam(const QString name, const QString color);

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
    QList<TeamDto> list;
};

