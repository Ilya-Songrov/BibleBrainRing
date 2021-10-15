#pragma once

#include <QObject>
#include <QHostAddress>
#include <QTcpSocket>
#include <QDataStream>
#include <QTimer>
#include <QQueue>
#include <QJsonDocument>

class ReadWriteSocket : public QTcpSocket
{
    Q_OBJECT
public:
    enum DataCompletenessCheck{
        JSONValid,
        QDataStream_5_15,
    };
    explicit ReadWriteSocket(const DataCompletenessCheck dataCompletenessCheck, QObject *parent = nullptr);
    virtual ~ReadWriteSocket();

    void sendDataToHost(const QByteArray &arr, const int timeout);
    QString getAddressPort() const;

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

private:
    struct TransferData{
        QByteArray arr;
        qint64 sizeAllData              = 0;
        qint64 alreadyTransitingBytes   = 0;
        int timeout                     = -1;

        inline bool isDataInTransit() { return sizeAllData != TransferData{}.sizeAllData; };
    };

    QQueue<TransferData> queueTransferData;
    QDataStream dataStreamIn;
    TransferData currentTransferDataWrite;
    QTimer timerWrite;
    DataCompletenessCheck _dataCompletenessCheck;
};

