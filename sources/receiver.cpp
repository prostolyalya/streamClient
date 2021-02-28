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
    socket->deleteLater();
}

void Receiver::setAddress(const QHostAddress &value)
{
    address = value;
}

void Receiver::connecting()
{
    socket->reset();
    socket->connectToHost(address, 6001);
}

void Receiver::clearTmpFile()
{
    file->resize(0);
}
