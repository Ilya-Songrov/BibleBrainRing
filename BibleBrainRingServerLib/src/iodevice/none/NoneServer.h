#pragma once

#include <QObject>

#include "../iodeviceserverabstract.h"

class NoneServer : public IODeviceServerAbstract
{
public:
    explicit NoneServer(QObject *parent = nullptr);
    virtual ~NoneServer();

    virtual bool initServer();

    virtual void sendToClient(const QString &guidClient, const QByteArray &arr, const int writeTimeout);
    virtual void broadcast(const QByteArray &arr, const int writeTimeout = 5000);

    virtual void pauseAcceptingClients();
    virtual void resumeAcceptingClients();

    virtual  bool containsClient(const QString &guidClient) const;
    virtual  int getQuantityClients() const;
};

