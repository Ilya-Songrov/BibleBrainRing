#pragma once

#include <QObject>
#include <QHostAddress>
#include <QTcpSocket>
#include <QDataStream>
#include <QTimer>
#include <QQueue>
#include <QJsonDocument>

class ReadWriteSocket : public QObject
{
    Q_OBJECT
public:
    enum DataCompletenessCheck{
        JSONValid,
        QDataStream_5_15,
    };
    explicit ReadWriteSocket(const DataCompletenessCheck dataCompletenessCheck, QTcpSocket *socket = nullptr, QObject *parent = nullptr);
    virtual ~ReadWriteSocket();

    void sendDataToHost(const QByteArray &arr, const int timeout);
    QString getPeerAddressPort() const;
    QString getLocalAddressPort() const;

    void connectToHost(const QHostAddress &address, quint16 port);
    bool waitForConnected(const int msecs = 30000);
    void abort();

signals:
    void dataReceivedFromHost(const QByteArray &arr);
    void errorWriteTimeout();
    void errorOccurred(QAbstractSocket::SocketError);
    void stateChanged(QAbstractSocket::SocketState);
    void disconnected();
    void connected();
    void hostFound();

private slots:
    void handleBytesWritten(qint64 bytes);
    void handleReadyRead();
    void handleWriteTimeout();
    void finishCurrentTransferDataWrite();

    void saveTransferData(const QByteArray &arr, const int timeout);

private:
    struct TransferData{
        QByteArray arr;
        qint64 sizeAllData              = 0;
        qint64 alreadyTransitingBytes   = 0;
        int timeout                     = -1;

        inline bool isDataInTransit() { return sizeAllData != TransferData{}.sizeAllData; };
    };

    QScopedPointer<QTcpSocket> _socket;
    QQueue<TransferData> queueTransferData;
    QDataStream dataStreamIn;
    TransferData currentTransferDataWrite;
    QTimer timerWrite;
    DataCompletenessCheck _dataCompletenessCheck;
};

