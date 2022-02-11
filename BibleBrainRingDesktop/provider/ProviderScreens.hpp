#pragma once

#include <QObject>

#include "ManagerScreens.hpp"

class ProviderScreens : public QObject
{
    Q_OBJECT

public:
    explicit ProviderScreens(QObject *parent = nullptr);

    Q_INVOKABLE QVariantList getInfoAdditionalScreens();
    Q_INVOKABLE QSizeF getSizeForScreenWidget(const QSizeF boundingSize);

signals:

};

