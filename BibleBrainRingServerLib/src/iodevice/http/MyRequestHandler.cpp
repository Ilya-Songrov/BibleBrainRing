#include "MyRequestHandler.hpp"

namespace stefanfrings {

MyRequestHandler::MyRequestHandler(QObject* parent)
    :HttpRequestHandler(parent)
{
    qDebug("MyRequestHandler: created");
}


MyRequestHandler::~MyRequestHandler()
{
    qDebug("MyRequestHandler: deleted");
}

void MyRequestHandler::service(HttpRequest& request, HttpResponse& response)
{
    QByteArray path=request.getPath();
    qDebug("Conroller: path=%s",path.data());

    // Set a response header
    response.setHeader("Content-Type", "text/html; charset=ISO-8859-1");

    // Return a simple HTML document
    response.write("<html><body>Hello World!</body></html>",true);

    qDebug("MyRequestHandler: finished request");
}

}
