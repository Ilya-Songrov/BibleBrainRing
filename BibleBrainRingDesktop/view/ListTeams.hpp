#pragma once

#include <QObject>
#include <QDebug>

#include "biblebrainringserverlib/dtos/teamdto.h"

class ListTeams : public QObject
{
    Q_OBJECT
public:
    explicit ListTeams(QObject *parent = nullptr);

    void appendTeam(const TeamDto& team);
    void removeTeam(const TeamDto& team);
    void removeTeam(const int index);
    void clear();

    int getSize() const;
    TeamDto getTeam(const int index);
    QList<TeamDto>& getList();

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
    QList<TeamDto> list;
};

