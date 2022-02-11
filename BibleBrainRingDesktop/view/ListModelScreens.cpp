#include "ListModelScreens.hpp"

ListModelScreens::ListModelScreens(QObject *parent)
    : QAbstractListModel{parent}
    , mList(nullptr)
{

}

ListModelScreens::~ListModelScreens()
{

}

int ListModelScreens::rowCount(const QModelIndex& parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid() || !mList)
        return 0;

    return mList->getSize();
}

QVariant ListModelScreens::data(const QModelIndex& index, int role) const
{
    if (!index.isValid() || !mList)
        return QVariant();

    const AdditionalScreen screen = mList->getScreen(index.row());

    switch (role) {
    case XPos:
        return QVariant(screen.xPos);
    case YPos:
        return QVariant(screen.yPos);
    case WidthReal:
        return QVariant(screen.widthReal);
    case HeightReal:
        return QVariant(screen.heightReal);
    case WidthVisual:
        return QVariant(screen.widthVisual);
    case HeightVisual:
        return QVariant(screen.heightVisual);
    case ScalePixelSize:
        return QVariant(screen.scalePixelSize);
    }

    return QVariant();
}

bool ListModelScreens::setData(const QModelIndex& index, const QVariant& value, int role)
{
    const int position = index.row();
    if (position < 0 || listScreens()->getSize() <= position || mList == nullptr) {
        return false;
    }

    if(role == XPos) {
        listScreens()->getList()[position].xPos = value.toInt();
    }
    else if(role == YPos) {
        listScreens()->getList()[position].yPos = value.toInt();
    }
    else if(role == WidthReal) {
        listScreens()->getList()[position].widthReal = value.toInt();
    }
    else if(role == HeightReal) {
        listScreens()->getList()[position].heightReal = value.toInt();
    }
    else if(role == WidthVisual) {
        listScreens()->getList()[position].widthVisual = value.toInt();
    }
    else if(role == HeightVisual) {
        listScreens()->getList()[position].heightVisual = value.toInt();
    }
    else if(role == ScalePixelSize) {
        listScreens()->getList()[position].scalePixelSize = value.toDouble();
    }
    emit dataChanged(index, index, {role});
    return true;
}

Qt::ItemFlags ListModelScreens::flags(const QModelIndex& index) const
{
    if (!index.isValid()){
        return Qt::NoItemFlags;
    }

    return QAbstractItemModel::flags(index);
}

QHash<int, QByteArray> ListModelScreens::roleNames() const
{
    QHash<int, QByteArray> names;
    names[XPos              ] = "xPos";
    names[YPos              ] = "yPos";
    names[WidthReal         ] = "widthReal";
    names[HeightReal        ] = "heightReal";
    names[WidthVisual       ] = "widthVisual";
    names[HeightVisual      ] = "heightVisual";
    names[ScalePixelSize    ] = "scalePixelSize";
    return names;
}

ListScreens* ListModelScreens::listScreens() const
{
    return mList;
}

void ListModelScreens::setListScreens(ListScreens* listScreens)
{
    beginResetModel();

    if (mList){
        mList->disconnect(this);
    }

    mList = listScreens;

    if (mList) {

        connect(mList, &ListScreens::preResetModel, this, [=]() {
            beginResetModel();
        });
        connect(mList, &ListScreens::postResetModel, this, [=]() {
            endResetModel();
        });

        connect(mList, &ListScreens::preSetItems, this, [=](int count) {
            const int index = mList->getSize();
            beginInsertRows(QModelIndex(), index, index + count - 1);
        });
        connect(mList, &ListScreens::postSetItems, this, [=]() {
            endInsertRows();
        });

        connect(mList, &ListScreens::preRemoveItems, this, [=](int first, int last) {
            beginRemoveRows(QModelIndex(), first, last);
        });
        connect(mList, &ListScreens::postRemoveItems, this, [=]() {
            endRemoveRows();
        });
    }

    endResetModel();
}

