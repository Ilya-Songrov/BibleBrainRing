#pragma once

#include "../httpserver/httprequesthandler.h"
#include "utils/FileWorker.hpp"
#include "dtos/AllDtos.hpp"

class MyRequestHandler : public stefanfrings::HttpRequestHandler {
    Q_OBJECT
    Q_DISABLE_COPY(MyRequestHandler)
public:

    /**
      Constructor.
      @param parent Parent object
    */
    MyRequestHandler(std::function<TeamDto(QString guidTeam)> funcGetTeam, bool* acceptClients, QObject* parent = nullptr);

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

signals:
    void joinedClient(const DtoTeamRegistrationClientRs teamRegistrationDto);
    void buttonPressed(const DtoButtonPressedRq buttonPressedRq);

private:
    const QByteArray rootPath;
    std::function<TeamDto(QString guidTeam)> _funcGetTeam;
    bool* _acceptClients;
};
