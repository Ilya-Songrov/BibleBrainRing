#include "ListModel.hpp"

ListModel::ListModel(QObject *parent)
    : QAbstractListModel{parent}
    , mList(nullptr)
{

}

ListModel::~ListModel()
{

}

int ListModel::rowCount(const QModelIndex& parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid() || !mList)
        return 0;

    return mList->getSize();
}

QVariant ListModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid() || !mList)
        return QVariant();

    const TeamDto team = mList->getTeam(index.row());

    switch (role) {
    case Name:
        return QVariant(team.name);
    case Color:
        return QVariant(team.color);
    case Score:
        return QVariant(team.score);
    case Position:
        return QVariant(team.position);
    case Status:
        return QVariant(int(team.status));
    }

    return QVariant();
}

bool ListModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    qDebug() << "print_function:" << __FUNCTION__ << __LINE__ << " text: " << __LINE__ << Qt::endl;
    const int position = index.row();
    if (position < 0 || listTeams()->getSize() <= position || mList == nullptr) {
        return false;
    }
    qDebug() << "print_function:" << __FUNCTION__ << __LINE__ << " text: " << __LINE__ << Qt::endl;

    if(role == Name) {
        listTeams()->getList()[position].name = value.toString();
    }
    else if(role == Color) {
        listTeams()->getList()[position].color = value.toString();
    }
    else if(role == Score) {
        listTeams()->getList()[position].score = value.toDouble();
    }
    else if(role == Position) {
        listTeams()->getList()[position].position = value.toInt();
    }
    else if(role == Status) {
        listTeams()->getList()[position].status = TeamStatus(value.toInt());
    }
    emit dataChanged(index, index, {role});
    qDebug() << "print_function:" << __FUNCTION__ << __LINE__ << " role: " << role << Qt::endl;
    return true;
}

Qt::ItemFlags ListModel::flags(const QModelIndex& index) const
{
    if (!index.isValid()){
        return Qt::NoItemFlags;
    }

    return QAbstractItemModel::flags(index);
}

QHash<int, QByteArray> ListModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[Name]     = "name";
    names[Color]    = "color";
    names[Score]    = "score";
    names[Position] = "position";
    names[Status]   = "status";
    return names;
}

ListTeams* ListModel::listTeams() const
{
    return mList;
}

void ListModel::setListTeams(ListTeams* listTeams)
{
    beginResetModel();

    if (mList){
        mList->disconnect(this);
    }

    mList = listTeams;

    if (mList) {

        connect(mList, &ListTeams::preResetModel, this, [=]() {
            beginResetModel();
        });
        connect(mList, &ListTeams::postResetModel, this, [=]() {
            endResetModel();
        });

        connect(mList, &ListTeams::preSetItems, this, [=](int count) {
            const int index = mList->getSize();
            beginInsertRows(QModelIndex(), index, index + count - 1);
        });
        connect(mList, &ListTeams::postSetItems, this, [=]() {
            endInsertRows();
        });

        connect(mList, &ListTeams::preRemoveItems, this, [=](int first, int last) {
            beginRemoveRows(QModelIndex(), first, last);
        });
        connect(mList, &ListTeams::postRemoveItems, this, [=]() {
            endRemoveRows();
        });
    }

    endResetModel();
}

void ListModel::changeScore(const QVariant value, const int index)
{
    auto modelIndex = createIndex(index, 0);
    setData(modelIndex, value, Score);
    qDebug() << "print_function:" << __FUNCTION__ << __LINE__ << " text: " << __LINE__ << Qt::endl;
}

