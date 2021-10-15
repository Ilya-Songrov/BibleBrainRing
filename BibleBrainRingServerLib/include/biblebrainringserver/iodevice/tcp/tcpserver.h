#pragma once

#include <QObject>
#include <QTcpServer>

#include "iodevice/iodeviceserverabstract.h"
#include "readwritesocket.h"

class TcpServer : public IODeviceServerAbstract
{
    Q_OBJECT
public:
    explicit TcpServer(const QString& address, const QString& port, QObject *parent = nullptr);
    virtual ~TcpServer();

    virtual bool initServer();

    virtual void sendToClient(const QString &guidClient, const QByteArray &arr, const int writeTimeout);
    virtual void broadcast(const QByteArray &arr, const int writeTimeout = 5000);

    virtual void pauseAcceptingClients();
    virtual void resumeAcceptingClients();

    virtual  bool containsClient(const QString &guidClient) const;
    virtual  int getQuantityClients() const;

signals:
    void serverErrorOccurred(const QAbstractSocket::SocketError socketError);
    void clientErrorOccurred(const QAbstractSocket::SocketError socketError, const ReadWriteSocket* client);
    void clientStatusChanged(const QAbstractSocket::SocketState socketState, const ReadWriteSocket* client);
    void disconnectedClient(const ReadWriteSocket *client);

protected:
    virtual void incomingConnection(qintptr handle);

private:
    void removeClient(const ReadWriteSocket *clientSocket);
    ReadWriteSocket *findClient(const QString &guidClient) const;

private:
    QTcpServer tcpServer;
    QList<ReadWriteSocket*> listClients;
    const QString _address;
    const QString _port;
    const ReadWriteSocket::DataCompletenessCheck _dataCompletenessCheck;
};

