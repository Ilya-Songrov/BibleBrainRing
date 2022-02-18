#include "HttpServer.hpp"

HttpServer::HttpServer(const QString& host, const QString& port)
    : IODeviceServerAbstract{nullptr}
    , _host(host)
    , _port(port)
    , httpListener(nullptr)
    , myRequestHandler(nullptr)
    , _funcGetTeam(nullptr)
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
    settings->setValue("minLevel"           , "INFO");
    ;
    myRequestHandler = new MyRequestHandler(BibleBrainRingServerClassical::getTeam, &acceptClients, this);
    httpListener = new stefanfrings::HttpListener(settings, myRequestHandler, this);
    connect(myRequestHandler, &MyRequestHandler::joinedClient, this, &IODeviceServerAbstract::joinedClient, Qt::DirectConnection);
    connect(myRequestHandler, &MyRequestHandler::buttonPressed, this, &IODeviceServerAbstract::buttonPressed, Qt::DirectConnection);
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

void HttpServer::setFunctionGetTeam(std::function<TeamDto (QString)> funcGetTeam)
{
    _funcGetTeam = funcGetTeam;
}

