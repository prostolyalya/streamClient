#include "receiver.h"
#include <QFile>
#include <QHostAddress>

Receiver::Receiver(QString path, QObject *parent)
    : QObject(parent)
    , tmp_path(path)

{
    socket = std::make_unique<QTcpSocket>();
    connect(socket.get(), &QTcpSocket::readyRead, this, &Receiver::slotRead);
    connect(socket.get(), &QTcpSocket::disconnected, this, &Receiver::slotDisconnected);
    file = std::make_unique<QFile>(tmp_path);
    file.get()->open(QIODevice::Append | QIODevice::WriteOnly);
    file->resize(0);
    connect(socket.get(), &QTcpSocket::errorOccurred, this , &Receiver::errorSocket);
}

Receiver::~Receiver()
{
    file.get()->close();
    file.get()->remove();
}

void Receiver::slotRead()
{
    while (socket->bytesAvailable() > 0)
    {
        QByteArray data = "";
        data = socket.get()->readAll();

        file.get()->write(data);
        file_size = file.get()->size();
    }
}

void Receiver::slotDisconnected()
{
    socket->reset();
//    socket->deleteLater();
}

void Receiver::errorSocket(QAbstractSocket::SocketError err)
{
    qDebug() << "ERROR receiver" << err;
}

void Receiver::setAddress(const QHostAddress &value)
{
    address = value;
}

QAbstractSocket::SocketState Receiver::socketState()
{
    return socket->state();
}

void Receiver::connecting()
{
    socket->connectToHost(address, 6001);
}

void Receiver::clearTmpFile()
{
    file->resize(0);
}
