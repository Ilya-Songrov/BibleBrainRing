#pragma once

#include "../httpserver/httprequesthandler.h"

namespace stefanfrings {

/**
  The request handler receives incoming HTTP requests and generates responses.
*/

class MyRequestHandler : public HttpRequestHandler {
    Q_OBJECT
    Q_DISABLE_COPY(MyRequestHandler)
public:

    /**
      Constructor.
      @param parent Parent object
    */
    MyRequestHandler(QObject* parent=0);

    /**
      Destructor
    */
    ~MyRequestHandler();

    /**
      Process an incoming HTTP request.
      @param request The received HTTP request
      @param response Must be used to return the response
    */
    void service(HttpRequest& request, HttpResponse& response);

};

}
