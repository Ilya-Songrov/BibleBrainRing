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

#pragma once

#include <QObject>
#include <QJsonObject>
#include <QCoreApplication>

#include "readwritesocket.h"
#include "informationconsoleprinter.h"

class TcpClient : public QObject
{
    Q_OBJECT
public:
    explicit TcpClient(QObject *parent = nullptr);

    bool connectToServer(const QString& address, const quint16 port);
    bool getConnectStatus();

    void sendToServerStatus(const QJsonObject &obj, const QString &value_method);

    QString getAddressPort();

signals:
    void dataReceivedFromServer(const QString &mode, const QString &status, const int timeout,
                                const QString& message_to_display = QString(),
                                const QJsonValue &valueData = QJsonValue::Null);
    void projectInfoFromServerReceived(const QString &projectInfoFromServer);

private slots:
    void parseServerResponse(const QByteArray& arr);

private:
    ReadWriteSocket readWriteSocket;
    const int timeout;
    bool connectStatus;
};
