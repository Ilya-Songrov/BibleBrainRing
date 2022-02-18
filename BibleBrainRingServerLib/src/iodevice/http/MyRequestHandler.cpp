#include "MyRequestHandler.hpp"


MyRequestHandler::MyRequestHandler(std::function<TeamDto(QString guidTeam)> funcGetTeam, bool* acceptClients, QObject* parent)
    : HttpRequestHandler(parent)
    , rootPath(":/all_files/web-frontend")
    , _funcGetTeam(funcGetTeam)
    , _acceptClients(acceptClients)
{
    qDebug() << "print_function:" << __FUNCTION__ << __LINE__ << Qt::endl;
}

MyRequestHandler::~MyRequestHandler()
{
    qDebug() << "print_function:" << __FUNCTION__ << __LINE__ << Qt::endl;
}

void MyRequestHandler::service(stefanfrings::HttpRequest& request, stefanfrings::HttpResponse& response)
{
    static const QString page_registration_page = "registration-page";
    static const QString page_waiting_hall = "waiting-hall";
    static const QString page_button = "button";
    static const QString page_referee = "referee";
    static const QString page_wrong = "wrong";
    static QString guidReferee;
    const QByteArray path = request.getPath();
    qDebug() << "print_function:" << __FUNCTION__ << __LINE__ << " Start handller. path: " << path << Qt::endl;

    QString guid = request.getParameter("guid");
    QString status("success");
    QString error;
    if(path == "/check-guid"){
        if (guid.isEmpty()) { guid = QUuid::createUuid().toString(); }
        const TeamDto team = _funcGetTeam (guid);
        QString page;
        qDebug() << "print_function:" << __FUNCTION__ << __LINE__ << " team.status: " << team.status << Qt::endl;
        if (team.status == TeamStatus::Registered || team.status == TeamStatus::WaitingForTheNextRound) {
            page = page_waiting_hall;
        }
        else if(team.status == TeamStatus::InBattle){
            page = page_button;
        }
        else if(guid == guidReferee){
            page = page_referee;
        }
        else{
            page = page_registration_page;
        }
        QJsonObject obj{
            {"status", status},
            {"page", page},
            {"guid", guid},
            {"error", error},
        };
        response.write(QJsonDocument(obj).toJson(), true);
        qDebug() << "print_function:" << __FUNCTION__ << __LINE__ << " path: " << path << " obj: " << obj << Qt::endl;
    }
    else if(path == "/register"){
        const TeamDto team = _funcGetTeam (guid);
        if (*_acceptClients && team.guid.isEmpty()) {
            const QString name = request.getParameter("name");
            const QString color = request.getParameter("color");
            DtoTeamRegistrationClientRs rs;
            rs.guid     = guid;
            rs.name     = name;
            rs.color    = color;
            emit joinedClient(rs);
        }
        else{
            status = "error";
            error = "Registration failed";
        }
        QJsonObject obj{
            {"status", status},
            {"error", error},
        };
        response.write(QJsonDocument(obj).toJson(), true);
        qDebug() << "print_function:" << __FUNCTION__ << __LINE__ << " path: " << path << " obj: " << obj << Qt::endl;
    }
    else if(path == "/button-pressed"){
        const TeamDto team = _funcGetTeam (guid);
        const QString time = request.getParameter("time");
        QString page;
        bool ok = false;
        DtoButtonPressedRq buttonPressedRq;
        buttonPressedRq.guid = guid;
        buttonPressedRq.time = QString(time).toLongLong(&ok);
        if (!ok) {
            qWarning() << "time is not valid:" << time << Qt::endl;
            buttonPressedRq.time = QDateTime::currentSecsSinceEpoch();
        }
        if (team.status == TeamStatus::InBattle) {
            emit buttonPressed(buttonPressedRq);
        }
        else{
            status = "redirect";
            page = page_waiting_hall;
        }
        QJsonObject obj{
            {"status", status},
            {"page", page},
            {"error", error},
        };
        response.write(QJsonDocument(obj).toJson(), true);
        qDebug() << "print_function:" << __FUNCTION__ << __LINE__ << " path: " << path << " obj: " << obj << Qt::endl;
    }
    else if(path == "/referee-reset"){
        const QString time = request.getParameter("time");
        bool ok = false;
        qint64 timeNum = QString(time).toLongLong(&ok);
        if (!ok) {
            qWarning() << "time is not valid:" << time << Qt::endl;
            timeNum = QDateTime::currentSecsSinceEpoch();
        }
        emit refereeReset(timeNum);
        QJsonObject obj{
            {"status", status},
            {"error", error},
        };
        response.write(QJsonDocument(obj).toJson(), true);
        qDebug() << "print_function:" << __FUNCTION__ << __LINE__ << " path: " << path << " obj: " << obj << Qt::endl;
    }
    else if(path == "/referee-start-time"){
        const QString time = request.getParameter("time");
        bool ok = false;
        qint64 timeNum = QString(time).toLongLong(&ok);
        if (!ok) {
            qWarning() << "time is not valid:" << time << Qt::endl;
            timeNum = QDateTime::currentSecsSinceEpoch();
        }
        emit refereeStartTime(timeNum);
        QJsonObject obj{
            {"status", status},
            {"error", error},
        };
        response.write(QJsonDocument(obj).toJson(), true);
        qDebug() << "print_function:" << __FUNCTION__ << __LINE__ << " path: " << path << " obj: " << obj << Qt::endl;
    }
    else if(path == "/" + page_waiting_hall){
        response.write(FileWorker::readFile(rootPath + path + ".html"), true);
        qDebug() << "print_function:" << __FUNCTION__ << __LINE__ << " path: " << path << Qt::endl;
    }
    else if(path == "/" + page_button){
        response.write(FileWorker::readFile(rootPath + path + ".html"), true);
        qDebug() << "print_function:" << __FUNCTION__ << __LINE__ << " path: " << path << Qt::endl;
    }
    else if(path == "/" + page_wrong){
        response.write(FileWorker::readFile(rootPath + path + ".html"), true);
        qDebug() << "print_function:" << __FUNCTION__ << __LINE__ << " path: " << path << Qt::endl;
    }
    else if(path == "/" + page_referee){
        if (guid.isEmpty()) { guid = QUuid::createUuid().toString(); }
        guidReferee = guid;
        response.write(FileWorker::readFile(rootPath + path + ".html"), true);
        qDebug() << "print_function:" << __FUNCTION__ << __LINE__ << " path: " << path << Qt::endl;
    }
    else if(path == "/" + page_registration_page || path == "/"){
        response.write(FileWorker::readFile(rootPath + "/" + page_registration_page + ".html"), true);
        qDebug() << "print_function:" << __FUNCTION__ << __LINE__ << " path: " << path << Qt::endl;
    }
    else if(!path.isEmpty()){
        response.write(FileWorker::readFile(rootPath + path), true);
        qDebug() << "print_function:" << __FUNCTION__ << __LINE__ << " path: " << path << Qt::endl;
    }

    qDebug() << "print_function:" << __FUNCTION__ << __LINE__ << " Finish handller. path: " << path << Qt::endl;
}
