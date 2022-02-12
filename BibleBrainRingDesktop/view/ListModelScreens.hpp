#pragma once

#include <QDebug>
#include <QAbstractListModel>

#include "ListScreens.hpp"

class ListModelScreens : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(ListScreens* listScreens READ listScreens WRITE setListScreens)

public:
    enum {
        XPos            = Qt::UserRole + 1,
        YPos            ,
        WidthReal       ,
        HeightReal      ,
        WidthVisual     ,
        HeightVisual    ,
        ScalePixelSize  ,
    };

    explicit ListModelScreens(QObject *parent = nullptr);
    ~ListModelScreens();

    ListModelScreens(ListModelScreens const &) = delete;
    void operator=(ListModelScreens const &) = delete;

    // Basic functionality:
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    virtual bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    virtual Qt::ItemFlags flags(const QModelIndex& index) const override;

    virtual QHash<int, QByteArray> roleNames() const override;

    ListScreens* listScreens() const;
    void setListScreens(ListScreens* listScreens);

private:
    ListScreens* mList;
};

