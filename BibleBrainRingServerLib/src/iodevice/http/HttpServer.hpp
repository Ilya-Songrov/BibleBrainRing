#pragma once

#include <QObject>
#include <QUuid>

#include "iodevice/iodeviceserverabstract.h"
#include "enums/global_enums.h"
#include "dtos/teamdto.h"
#include "httplistener.h"
#include "MyRequestHandler.hpp"

class HttpServer : public IODeviceServerAbstract
{
public:
    explicit HttpServer(const QString& host, const QString& port, QObject *parent = nullptr);
    virtual ~HttpServer();

    virtual bool initServer();

    virtual void sendToClient(const QString &guidClient, const QByteArray &arr, const int writeTimeout);
    virtual void broadcast(const QByteArray &arr, const int writeTimeout = 5000);

    virtual void stopAcceptingClients();
    virtual void startAcceptingClients();

private:

private:
    const QString _host;
    const QString _port;
    MyRequestHandler myRequestHandler;
    stefanfrings::HttpListener* httpListener;
};

