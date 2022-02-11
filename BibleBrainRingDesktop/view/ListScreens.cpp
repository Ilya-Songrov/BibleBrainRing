#include "ListScreens.hpp"

ListScreens::ListScreens(QObject *parent)
    : QObject{parent}
{

}

void ListScreens::appendTeam(const AdditionalScreen& screen)
{
    emit preSetItems(1);
    list.append(screen);
    emit postSetItems();
}

void ListScreens::removeTeam(const int index)
{
    if (index > -1 && list.size() > index) {
        emit preRemoveItems(index, index);
        list.removeAt(index);
        emit postRemoveItems();
    }
}

void ListScreens::clear()
{
    emit preResetModel();
    list.clear();
    emit postResetModel();
}

AdditionalScreen ListScreens::getScreen(const int index)
{
    if (index > -1 && list.size() > index) {
        return list.at(index);
    }
    return {};
}

QList<AdditionalScreen>& ListScreens::getList()
{
    return list;
}

int ListScreens::getSize() const
{
    return list.size();
}
