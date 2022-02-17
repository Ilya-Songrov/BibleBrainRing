#include "HttpServer.hpp"

#include "MyRequestHandler.hpp"

HttpServer::HttpServer(const QString& host, const QString& port, std::function<TeamDto(QString guidTeam)> funcGetTeam, QObject *parent)
    : IODeviceServerAbstract{parent}
    , _host(host)
    , _port(port)
    , httpListener(nullptr)
    , _funcGetTeam(funcGetTeam)
{

}

HttpServer::~HttpServer()
{

}

bool HttpServer::initServer()
{
    QSettings* settings = new QSettings(this);
    settings->setValue("host"               , _host);
    settings->setValue("port"               , _port);
    settings->setValue("minThreads"         , "4");
    settings->setValue("maxThreads"         , "100");
    settings->setValue("cleanupInterval"    , "60000");
    settings->setValue("readTimeout"        , "60000");
    settings->setValue("maxRequestSize"     , "16000");
    settings->setValue("maxMultiPartSize"   , "10000000");
    httpListener = new stefanfrings::HttpListener(settings, new MyRequestHandler(_funcGetTeam, &acceptClients, this), this);
    return httpListener->isListening();
}

void HttpServer::sendToClient(const QString& /*guidClient*/, const QByteArray& /*arr*/, const int /*writeTimeout*/)
{

}

void HttpServer::broadcast(const QByteArray& /*arr*/, const int /*writeTimeout*/)
{

}

void HttpServer::stopAcceptingClients()
{
    acceptClients = false;
}

void HttpServer::startAcceptingClients()
{
    acceptClients = true;
}

