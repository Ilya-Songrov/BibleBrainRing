#include "MyRequestHandler.hpp"


MyRequestHandler::MyRequestHandler(QObject* parent)
    : HttpRequestHandler(parent)
    , rootPath("/home/songrov/DeveloperRoot/AllProjects/Ilya_Songrov/BibleBrainRing/BibleBrainRing/BibleBrainRingServerLib/src/iodevice/http/web-frontend")
{
    qDebug() << "print_function:" << __FUNCTION__ << __LINE__ << Qt::endl;
}

MyRequestHandler::~MyRequestHandler()
{
    qDebug() << "print_function:" << __FUNCTION__ << __LINE__ << Qt::endl;
}

void MyRequestHandler::service(stefanfrings::HttpRequest& request, stefanfrings::HttpResponse& response)
{
    const QByteArray path = request.getPath();
    qDebug() << "print_function:" << __FUNCTION__ << __LINE__ << " path: " << path << Qt::endl;

    if (path == "/") {
        response.write(FileWorker::readFile(rootPath), true);
    }
    else if(path == "/check-uuid"){
//        const

    }
    // Set a response header
    response.setHeader("Content-Type", "text/html; charset=ISO-8859-1");

    // Return a simple HTML document
    response.write("<html><body>Hello World!</body></html>",true);

    // /home/songrov/DeveloperRoot/AllProjects/Ilya_Songrov/BibleBrainRing/BibleBrainRing/BibleBrainRingServerLib/src/iodevice/http/web-frontend

    qDebug() << "print_function:" << __FUNCTION__ << __LINE__ << "finished request" << Qt::endl;
}
