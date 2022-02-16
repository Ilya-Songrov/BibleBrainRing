#include "HttpServer.hpp"

HttpServer::HttpServer(QObject *parent)
    : IODeviceServerAbstract{parent}
{

}

HttpServer::~HttpServer()
{

}

bool HttpServer::initServer()
{

}

void HttpServer::sendToClient(const QString& guidClient, const QByteArray& arr, const int writeTimeout)
{

}

void HttpServer::broadcast(const QByteArray& arr, const int writeTimeout)
{

}

void HttpServer::pauseAcceptingClients()
{

}

void HttpServer::resumeAcceptingClients()
{

}

bool HttpServer::containsClient(const QString& guidClient) const
{

}

int HttpServer::getQuantityClients() const
{

}
