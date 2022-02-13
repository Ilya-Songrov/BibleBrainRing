#include "readwritesocket.h"

ReadWriteSocket::ReadWriteSocket(const DataCompletenessCheck dataCompletenessCheck, QTcpSocket *socket, QObject *parent) : QObject(parent)
  , _socket(socket ? socket : new QTcpSocket())
  , currentTransferDataWrite(TransferData{})
  , _dataCompletenessCheck(dataCompletenessCheck)
{
    dataStreamIn.setDevice(_socket.get());
    dataStreamIn.setVersion(QDataStream::Qt_5_15);

    connect(&timerWrite,        &QTimer::timeout            , this, &ReadWriteSocket::handleWriteTimeout);
    connect(_socket.get(),            &QTcpSocket::bytesWritten   , this, &ReadWriteSocket::handleBytesWritten);
    connect(_socket.get(),            &QTcpSocket::readyRead      , this, &ReadWriteSocket::handleReadyRead);
    connect(_socket.get(),            &QTcpSocket::errorOccurred  , this, &ReadWriteSocket::errorOccurred  );
    connect(_socket.get(),            &QTcpSocket::stateChanged   , this, &ReadWriteSocket::stateChanged   );
    connect(_socket.get(),            &QTcpSocket::disconnected   , this, &ReadWriteSocket::disconnected   );
    connect(_socket.get(),            &QTcpSocket::connected      , this, &ReadWriteSocket::connected      );
    connect(_socket.get(),            &QTcpSocket::hostFound      , this, &ReadWriteSocket::hostFound      );
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
        saveTransferData(arr, timeout);
        return;
    }
    currentTransferDataWrite.sizeAllData    = block.size();
    currentTransferDataWrite.timeout        = timeout;
    const auto writingBytes = _socket->write(block);
    if (writingBytes == -1) {
        qCritical() << "writingBytes:" << writingBytes << "block:" << block << Qt::endl;
        saveTransferData(arr, timeout);
        QTimer::singleShot(100, [this](){ finishCurrentTransferDataWrite(); });
        return;
    }
    timerWrite.start(currentTransferDataWrite.timeout);
}

QString ReadWriteSocket::getPeerAddressPort() const
{
    return _socket->peerAddress().toString() + ":" + QString::number(_socket->peerPort());
}

QString ReadWriteSocket::getLocalAddressPort() const
{
    return _socket->localAddress().toString() + ":" + QString::number(_socket->localPort());
}

void ReadWriteSocket::connectToHost(const QHostAddress &address, quint16 port)
{
    _socket->connectToHost(address, port);
}

bool ReadWriteSocket::waitForConnected(const int msecs)
{
    return _socket->waitForConnected(msecs);
}

void ReadWriteSocket::abort()
{
    _socket->abort();
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
        arr = _socket->readAll();
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
    qDebug() << "function:" << Q_FUNC_INFO << __LINE__ << arr << Qt::endl;
}

void ReadWriteSocket::handleWriteTimeout()
{
    qWarning() << Q_FUNC_INFO << QString("Operation TimeoutWrite for LocalAddressPort (%1), Elapsed time (timerWrite: %2ms)").arg(this->getLocalAddressPort()).arg(timerWrite.remainingTime()) << Qt::endl;
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

void ReadWriteSocket::saveTransferData(const QByteArray &arr, const int timeout)
{
    TransferData transferData;
    transferData.arr            = arr;
    transferData.sizeAllData    = transferData.arr.size();
    transferData.timeout        = timeout;
    queueTransferData.enqueue(transferData);
}
