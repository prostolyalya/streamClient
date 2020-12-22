#include "sender.h"
#include <thread_pool.h>
Sender::Sender(QObject *parent)
    : QObject(parent)
{
    socket = std::make_unique<QTcpSocket>();
    connect(socket.get(), &QTcpSocket::readyRead, this, &Sender::readSocket);
    connect(socket.get(), &QTcpSocket::disconnected, this, &Sender::discardSocket);
}

void Sender::readSocket()
{
    if (socket.get()->bytesAvailable() > 0)
        qDebug() << socket->readAll();
}

void Sender::discardSocket()
{
    socket->deleteLater();
}

void Sender::setFile_path(const QString &value)
{
    file_path = value;
}

void Sender::connecting()
{
    socket->reset();
    socket->connectToHost("192.168.0.102", 6002);
}

void Sender::sendFile()
{
    QFile file(file_path);
    if (file.open(QFile::ReadOnly))
    {
        int size = 1024;
        for (int pos = 0; pos < file.size(); pos += 1024)
        {
            file.seek(pos);
            QByteArray data = file.read(size);
            while (socket->waitForReadyRead(5))
            {
            }
            socket->write(data);
        }
    }
    QStringList list = file_path.split('/');
    QString name = list.at(list.size() - 1);
    emit fileSent(file.size(), name);
    qDebug() << file.size();
}
