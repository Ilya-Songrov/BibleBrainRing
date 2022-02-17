#include "NoneServer.h"

NoneServer::NoneServer(QObject *parent)
    : IODeviceServerAbstract{parent}
{

}

NoneServer::~NoneServer()
{

}

bool NoneServer::initServer()
{
    return true;
}

void NoneServer::sendToClient(const QString& /*guidClient*/, const QByteArray& /*arr*/, const int /*writeTimeout*/)
{

}

void NoneServer::broadcast(const QByteArray& /*arr*/, const int /*writeTimeout*/)
{

}

void NoneServer::stopAcceptingClients()
{

}

void NoneServer::startAcceptingClients()
{

}

