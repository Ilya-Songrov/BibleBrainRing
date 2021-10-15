#include "biblebrainringserverlib/iodevice/tcp/readwritesocket.h"

ReadWriteSocket::ReadWriteSocket(const DataCompletenessCheck dataCompletenessCheck, QObject *parent) : QTcpSocket(parent)
  , currentTransferDataWrite(TransferData{})
  , _dataCompletenessCheck(dataCompletenessCheck)
{
    dataStreamIn.setDevice(this);
    dataStreamIn.setVersion(QDataStream::Qt_5_15);

    connect(&timerWrite,    &QTimer::timeout            , this, &ReadWriteSocket::handleWriteTimeout);
    connect(this,           &QTcpSocket::bytesWritten   , this, &ReadWriteSocket::handleBytesWritten);
    connect(this,           &QTcpSocket::readyRead      , this, &ReadWriteSocket::handleReadyRead);
    connect(this,           &QTcpSocket::errorOccurred  , this, &ReadWriteSocket::errorOccurred  );
    connect(this,           &QTcpSocket::stateChanged   , this, &ReadWriteSocket::stateChanged   );
    connect(this,           &QTcpSocket::disconnected   , this, &ReadWriteSocket::disconnected   );
    connect(this,           &QTcpSocket::connected      , this, &ReadWriteSocket::connected      );
    connect(this,           &QTcpSocket::hostFound      , this, &ReadWriteSocket::hostFound      );
}

ReadWriteSocket::~ReadWriteSocket()
{

}

void ReadWriteSocket::sendDataToHost(const QByteArray &arr, const int timeout)
{
    QByteArray block;
    if (_dataCompletenessCheck == DataCompletenessCheck::QDataStream_5_15) {
        QDataStream sendStream(&block, QIODevice::ReadWrite);
        sendStream << arr;
    }
    else if (_dataCompletenessCheck == DataCompletenessCheck::JSONValid) {
        block = arr;
    }

    if (currentTransferDataWrite.isDataInTransit()) {
        TransferData transferData;
        transferData.arr            = block;
        transferData.sizeAllData    = transferData.arr.size();
        transferData.timeout        = timeout;
        queueTransferData.enqueue(transferData);
        return;
    }
    currentTransferDataWrite.sizeAllData    = block.size();
    currentTransferDataWrite.timeout        = timeout;
    this->write(block);
    timerWrite.start(currentTransferDataWrite.timeout);
}

QString ReadWriteSocket::getPeerAddressPort() const
{
    return this->peerAddress().toString() + ":" + QString::number(this->peerPort());
}

QString ReadWriteSocket::getLocalAddressPort() const
{
    return this->localAddress().toString() + ":" + QString::number(this->localPort());
}

void ReadWriteSocket::handleBytesWritten(qint64 bytes)
{
    currentTransferDataWrite.alreadyTransitingBytes += bytes;

    if (currentTransferDataWrite.alreadyTransitingBytes == currentTransferDataWrite.sizeAllData) {
        finishCurrentTransferDataWrite();
        return;
    }

    if (!timerWrite.isActive()){
        timerWrite.start(currentTransferDataWrite.timeout);
    }
}

void ReadWriteSocket::handleReadyRead()
{
    QByteArray arr;
    if (_dataCompletenessCheck == JSONValid) {
        arr = this->readAll();
        if (QJsonDocument::fromJson(arr).isNull()) {
            return;
        }
    }
    else if (_dataCompletenessCheck == QDataStream_5_15) {
        dataStreamIn.startTransaction();
        dataStreamIn >> arr;

        if (!dataStreamIn.commitTransaction()){
            return;
        }
    }
    emit dataReceivedFromHost(arr);
}

void ReadWriteSocket::handleWriteTimeout()
{
    qWarning() << Q_FUNC_INFO << QString("Operation TimeoutWrite for port (%1), Elapsed time (timerWrite: %2ms)").arg(this->peerName()).arg(timerWrite.remainingTime()) << Qt::endl;
    finishCurrentTransferDataWrite();
}

void ReadWriteSocket::finishCurrentTransferDataWrite()
{
    timerWrite.stop();
    currentTransferDataWrite = TransferData{};
    if (!queueTransferData.isEmpty()) {
        const auto transferData = queueTransferData.dequeue();
        sendDataToHost(transferData.arr, transferData.timeout);
    }
}
