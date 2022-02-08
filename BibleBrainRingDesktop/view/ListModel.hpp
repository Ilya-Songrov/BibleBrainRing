#pragma once

#include <QDebug>
#include <QAbstractListModel>

#include "ListTeams.hpp"

class ListModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(ListTeams *listTeams READ listTeams WRITE setListTeams)

public:
    enum {
        Name     = Qt::UserRole + 1,
        Color   ,
        Score   ,
        Position,
        Status  ,
    };

    explicit ListModel(QObject *parent = nullptr);
    ~ListModel();

    ListModel(ListModel const &) = delete;
    void operator=(ListModel const &) = delete;

    // Basic functionality:
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    virtual bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    virtual Qt::ItemFlags flags(const QModelIndex& index) const override;

    virtual QHash<int, QByteArray> roleNames() const override;

    ListTeams* listTeams() const;
    void setListTeams(ListTeams* listTeams);

//    Q_INVOKABLE int getQuantityPositions();

private:
    ListTeams* mList;
};

