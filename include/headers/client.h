#ifndef CLIENT_H
#define CLIENT_H
#pragma once

#include <QtNetwork>
#include <QObject>

#include "sender.h"
#include "receiver.h"

class Client : public QObject
{
    Q_OBJECT
public:
    Client(int id, QObject* parent = nullptr);
    ~Client();


private:
    std::unique_ptr<QTcpSocket> socket;
    int id = 0;
    qint64 sizeFile = 0;
    std::unique_ptr<Sender> sender;
    std::unique_ptr<Receiver> receiver;

    QString current_path;
    QString fileName = "";

    void saveFile();

public:
    void connecting();

public slots:
    void slotRead();
    void slotServerDisconnected();
    void fileSent(qint64 size, QString fileName);
    void sendFile(QString path);
    void init();
    void sendMessage(QString text);
signals:
    void sendFileSignal();
    void clientDisconnect(int id);
    void messageReceived(QByteArray msg);
};
#endif // CLIENT_H
