#include "sender.h"
#include <thread_pool.h>
Sender::Sender(QObject *parent)
    : QObject(parent)
{
    socket = std::make_unique<QTcpSocket>();
    connect(socket.get(), &QTcpSocket::readyRead, this, &Sender::readSocket);
    connect(socket.get(), &QTcpSocket::disconnected, this, &Sender::discardSocket);
    connect(socket.get(), &QTcpSocket::errorOccurred, this , &Sender::errorSocket);
}

void Sender::readSocket()
{
    if (socket.get()->bytesAvailable() > 0)
        qDebug() << socket->readAll();
}

void Sender::discardSocket()
{
    socket->reset();
}

void Sender::connecting()
{
    socket->connectToHost(address, 6002);
}

void Sender::sendFile(QString file_path, bool isPrivate)
{
    QFile file(file_path);
    if (file.open(QFile::ReadOnly))
    {
        int size = 1024;
        for (int pos = 0; pos < file.size(); pos += 1024)
        {
            file.seek(pos);
            QByteArray data = file.read(size);
            while (socket->waitForBytesWritten(1))
            {
            }
            socket->write(data);
        }
    }
    QStringList list = file_path.split('/');
    QString name = list.at(list.size() - 1);
    emit fileSent(file.size(), name, isPrivate);
    qDebug() << file.size();
}

void Sender::errorSocket(QAbstractSocket::SocketError err)
{
    qDebug() << "ERROR sender" << err;
}

void Sender::setAddress(const QHostAddress &value)
{
    address = value;
}

QAbstractSocket::SocketState Sender::socketState()
{
    return socket->state();
}
