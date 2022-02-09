#include "ListTeams.hpp"

ListTeams::ListTeams(QObject *parent)
    : QObject{parent}
{

}

void ListTeams::appendTeam(const TeamDto& team)
{
    emit preSetItems(1);
    list.append(team);
    emit postSetItems();
}

void ListTeams::removeTeam(const TeamDto& team)
{
    const auto it = std::find_if(list.begin(), list.end(),
                                 [team](const TeamDto& t) { return t.guid == team.guid;});
    const auto first = std::distance(list.begin(), it);
    emit preRemoveItems(first, first);
    list.erase(list.begin(), it);
    emit postRemoveItems();
}

void ListTeams::removeTeam(const int index)
{
    if (index > -1 && list.size() > index) {
        emit preRemoveItems(index, index);
        list.removeAt(index);
        emit postRemoveItems();
    }
}

void ListTeams::clear()
{
    emit preResetModel();
    list.clear();
    emit postResetModel();
}

TeamDto ListTeams::getTeam(const int index)
{
    if (index > -1 && list.size() > index) {
        return list.at(index);
    }
    return {};
}

QList<TeamDto>& ListTeams::getList()
{
    return list;
}

int ListTeams::getSize() const
{
    return list.size();
}
