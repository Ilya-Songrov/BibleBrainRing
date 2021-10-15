#include "biblebrainringserverlib/iodevice/tcp/tcpserver.h"

TcpServer::TcpServer(const QString &address, const QString &port, QObject *parent) : IODeviceServerAbstract(parent)
  , _address(address)
  , _port(port)
  , _dataCompletenessCheck(ReadWriteSocket::JSONValid)
{
    connect(&tcpServer, &QTcpServer::newConnection, this, &TcpServer::incomingConnection);
}

TcpServer::~TcpServer()
{
    tcpServer.close();
}

bool TcpServer::initServer()
{
    connect(&tcpServer, &QTcpServer::acceptError, this, &TcpServer::serverErrorOccurred);

    if (!tcpServer.listen(QHostAddress(_address), _port.toUShort())) {
        emit serverStatusChanged(QString("Unable to start the server: %1.").arg(tcpServer.errorString()));
        return false;
    }
    emit serverStatusChanged(QString("TcpServer has started addressPort: (%1:%2)").arg(tcpServer.serverAddress().toString()).arg(tcpServer.serverPort()));
    return true;
}

void TcpServer::sendToClient(const QString &guidClient, const QByteArray &arr, const int writeTimeout)
{
    ReadWriteSocket *client = findClient(guidClient);
    if (!client) {
        qWarning() << "Error client is not exist: " << guidClient << Qt::endl;
        return;
    }
    client->sendDataToHost(arr, writeTimeout);
}

void TcpServer::broadcast(const QByteArray &arr, const int writeTimeout)
{
    for (const ReadWriteSocket* client: qAsConst(listClients)) {
        sendToClient(client->getPeerAddressPort(), arr, writeTimeout);
    }
}

void TcpServer::pauseAcceptingClients()
{
    tcpServer.pauseAccepting();
}

void TcpServer::resumeAcceptingClients()
{
    tcpServer.resumeAccepting();
}

bool TcpServer::containsClient(const QString &guidClient) const
{
    return findClient(guidClient) != nullptr;
}

int TcpServer::getQuantityClients() const
{
    return listClients.size();
}

void TcpServer::incomingConnection()
{
    QTcpSocket *socket = tcpServer.nextPendingConnection();
    ReadWriteSocket *client = new ReadWriteSocket(_dataCompletenessCheck, this);
    if (!client->setSocketDescriptor(socket->socketDescriptor())) {
        client->deleteLater();
        return;
    }
    listClients.append(client);
    connect(client, &ReadWriteSocket::disconnected,             this, std::bind(&TcpServer::removeClient, this, client));
    connect(client, &ReadWriteSocket::disconnected,             this, std::bind(&TcpServer::disconnectedClient, this, client));
    connect(client, &ReadWriteSocket::disconnected,             this, std::bind(&IODeviceServerAbstract::disconnectedClient, this, client->getPeerAddressPort()));
    connect(client, &ReadWriteSocket::disconnected,             client, &ReadWriteSocket::deleteLater);
    connect(client, &ReadWriteSocket::dataReceivedFromHost,     this, std::bind(&TcpServer::responseFromClient, this, client->getPeerAddressPort(), std::placeholders::_1));
    connect(client, &ReadWriteSocket::errorOccurred,            this, std::bind(&TcpServer::clientErrorOccurred, this, std::placeholders::_1, client));
    connect(client, &ReadWriteSocket::stateChanged,             this, std::bind(&TcpServer::clientStatusChanged, this, std::placeholders::_1, client));
    emit joinedClient(client->getPeerAddressPort());
}

void TcpServer::removeClient(const ReadWriteSocket *clientSocket)
{
    auto it = std::find_if(listClients.begin(), listClients.end(), [clientSocket](const ReadWriteSocket *client){ return client == clientSocket; });
    if (it != std::end(listClients)) {
        listClients.erase(it);
    }
}

ReadWriteSocket *TcpServer::findClient(const QString &guidClient) const
{
    auto it = std::find_if(listClients.begin(), listClients.end(), [guidClient](const ReadWriteSocket *client){ return client->getPeerAddressPort() == guidClient; });
    if (it == std::end(listClients)) {
        return nullptr;
    }
    return *it;
}
