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

class IODeviceServerAbstract : public QObject
{
    Q_OBJECT
public:
    enum ClientStatus{
        Undefined,
        Connected,
        Disconnected,
    };
    explicit IODeviceServerAbstract(QObject *parent = nullptr);
    virtual ~IODeviceServerAbstract();

    virtual bool initServer() = 0;

    virtual void sendToClient(const QString &guidClient, const QByteArray &arr, const int writeTimeout) = 0;
    virtual void broadcast(const QByteArray &arr, const int writeTimeout) = 0;

    virtual void pauseAcceptingClients() = 0;
    virtual void resumeAcceptingClients() = 0;

    virtual  bool containsClient(const QString &guidClient) const = 0;
    virtual  int getQuantityClients() const = 0;

signals:
    void joinedClient(const QString &guidClient);
    void disconnectedClient(const QString &guidClient);
    void responseFromClient(const QString &guidClient, const QByteArray &arr);
    void clientStatusChanged(const QString &guidClient, const ClientStatus clientStatus);
    void serverStatusChanged(const QString &status);

};

