#pragma once

#include "../httpserver/httprequesthandler.h"
#include "utils/FileWorker.hpp"

class MyRequestHandler : public stefanfrings::HttpRequestHandler {
    Q_OBJECT
    Q_DISABLE_COPY(MyRequestHandler)
public:

    /**
      Constructor.
      @param parent Parent object
    */
    MyRequestHandler(QObject* parent = nullptr);

    /**
      Destructor
    */
    ~MyRequestHandler();

    /**
      Process an incoming HTTP request.
      @param request The received HTTP request
      @param response Must be used to return the response
    */
    void service(stefanfrings::HttpRequest& request, stefanfrings::HttpResponse& response);

private:
    const QByteArray rootPath;

};
