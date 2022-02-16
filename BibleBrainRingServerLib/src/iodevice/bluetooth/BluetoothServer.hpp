#pragma once

#include <QObject>

#include "../iodeviceserverabstract.h"

class BluetoothServer : public IODeviceServerAbstract
{
public:
    explicit BluetoothServer(QObject *parent = nullptr);
};

