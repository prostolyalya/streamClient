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
}

void Receiver::slotRead()
{
    while (socket->bytesAvailable() > 0)
    {
        QByteArray data = socket->readAll();
        QFile file(tmp_path);
        file.open(QIODevice::Append | QIODevice::WriteOnly);
        file.write(data);
        file.close();
        file_size = file.size();
    }
}

void Receiver::slotDisconnected()
{
    socket->reset();
    socket->deleteLater();
}

void Receiver::connecting()
{
    socket->reset();
    socket->connectToHost("192.168.0.103", 6001);
}

void Receiver::clearTmpFile()
{
    QFile file(tmp_path);
    file.remove();
}
