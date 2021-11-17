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

#include "tcpclient.h"

TcpClient::TcpClient(QObject *parent) : QObject(parent)
  , readWriteSocket(ReadWriteSocket::QDataStream_5_15)
  , timeout(5000)
  , connectStatus(false)
{
    connect(&readWriteSocket, &ReadWriteSocket::dataReceivedFromHost, this, &TcpClient::parseServerResponse);
}

bool TcpClient::connectToServer(const QString &address, const quint16 port)
{
    InformationConsolePrinter::printArrAndMessage(QJsonDocument(), QString("%1 connect to (%2:%3)").arg(QCoreApplication::applicationName(), address).arg(port), QString(), false);
    readWriteSocket.abort();
    readWriteSocket.connectToHost(QHostAddress(address), port);
    const bool ret = readWriteSocket.waitForConnected(5000);
    if (ret) {
        InformationConsolePrinter::printArrAndMessage(QJsonDocument(), QString("%1 is connected to (%2) from (%3)").arg(QCoreApplication::applicationName(), readWriteSocket.getPeerAddressPort()
                                                                                                                           , readWriteSocket.getLocalAddressPort()), QString(), false);
    }
    else{
        InformationConsolePrinter::printArrAndMessage(QJsonDocument(), QString("%1 is not connected to (%2:%3)").arg(QCoreApplication::applicationName(), address).arg(port), QString(), true);
    }
    connectStatus = ret;
    return ret;
}

bool TcpClient::getConnectStatus()
{
    return connectStatus;
}

void TcpClient::sendToServerParams(const QJsonValue &valueParams, const QString &value_method)
{
    QJsonObject objRoot;
    objRoot.insert("method", value_method);
    objRoot.insert("params", valueParams);
    readWriteSocket.sendDataToHost(QJsonDocument(objRoot).toJson(), timeout);
}

QString TcpClient::getLocalAddressPort() const
{
    return readWriteSocket.getLocalAddressPort();
}

void TcpClient::parseServerResponse(const QByteArray &arr)
{
    const QJsonDocument doc = QJsonDocument::fromJson(arr);
    if (doc.isEmpty()) {
        InformationConsolePrinter::printArrAndMessage(QJsonDocument(), QString("Server response is empty"), QString(), true);
        return;
    }
    const QJsonObject objRoot = doc.object();
    InformationConsolePrinter::printArrAndMessage(doc, "SERVER --> CLIENT");
//    const bool isItNotification = objRoot.value(JsonKey::id) == QJsonValue::Null;
//    if (isItNotification) {
//        const bool notification_fridgemain_project_info = objRoot.value(JsonKey::method).toString() == JsonValue::notification_fridgemain_project_info;
//        const bool notification_fridgemain_state        = objRoot.value(JsonKey::method).toString() == JsonValue::notification_fridgemain_state;
//        if (notification_fridgemain_project_info) {
//            emit projectInfoFromServerReceived(objRoot.value(JsonKey::data).toString());
//        }
//        else if(notification_fridgemain_state){
//            const QString mode                  = objRoot.value(JsonKey::mode).toString();
//            const QString status                = objRoot.value(JsonKey::status).toString();
//            const int timeout                   = objRoot.value(JsonKey::timeout).toInt();
//            const QString message_to_display    = objRoot.value(JsonKey::message_to_display).toString();
//            const QJsonValue data               = objRoot.value(JsonKey::data);
//            emit dataReceivedFromServer(mode, status, timeout, message_to_display, data);
//        }
//        return;
//    }
//    else{
//        const bool command_fridgemain_init = objRoot.value(JsonKey::method).toString() == JsonValue::command_fridgemain_init;
//        if (command_fridgemain_init) {
//            sendToServerVersion(QCoreApplication::applicationVersion());
//        }
//    }
}
