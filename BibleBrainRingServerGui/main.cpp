/**************************************************************************
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 as published by the Free Software
** Foundation with exceptions as appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/.
**
**************************************************************************/

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>

#include "iodevice/tcp/tcpserver.h"
#include "server_classical/biblebrainringserverclassical.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    TcpServer tcpServer("127.0.0.1", "9090");
    BibleBrainRingServerClassical bibleBrainRingServerClassical(&tcpServer);
    const bool ret = bibleBrainRingServerClassical.initServer();
    if (!ret) {
        qWarning() << "Error server init" << Qt::endl;
        return 1;
    }
    bibleBrainRingServerClassical.startRegistration();
    bibleBrainRingServerClassical.onConnectNewTeam([](const TeamDto& team){ qDebug() << "new team:" << team.guid << Qt::endl; });
    bibleBrainRingServerClassical.onTeamDtoChanged([](const TeamDto& team){ qDebug() << "new team data:" << team.status << Qt::endl; });

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
