#ifndef RECEIVER_H
#define RECEIVER_H
#pragma once
#include <QTcpSocket>
#include <QObject>
#include <QFile>
#include <QHostAddress>
class Receiver : public QObject
{
    Q_OBJECT
public:
    Receiver(QString path, QObject* parent = nullptr);
    ~Receiver();
    void clearTmpFile();
    QString tmp_path = "";
    qint64 file_size = 0;
    std::unique_ptr<QFile> file;

    void setAddress(const QHostAddress& value);

    QTcpSocket::SocketState socketState();
public slots:
    void connecting();
    void slotRead();
    void slotDisconnected();
    void errorSocket(QAbstractSocket::SocketError err);
private:
    std::unique_ptr<QTcpSocket> socket;
    QHostAddress address;
};
#endif // RECEIVER_H
