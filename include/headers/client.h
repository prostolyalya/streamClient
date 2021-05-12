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
    Client(QObject* parent = nullptr);

private:
    std::unique_ptr<QTcpSocket> socket;
    qint64 sizeFile = 0;
    std::unique_ptr<Receiver> receiver;
    QHostAddress address;
    QString current_path;
    QString fileName = "";
    void saveFile();
public:
    void connecting();

    std::unique_ptr<Sender> sender;
    void setAddress(const QHostAddress &value);

public slots:
    void slotRead();
    void requestFile(QString file_name);
    void slotServerDisconnected();
    void fileSent(qint64 size, QString fileName, bool isPrivate);
    void sendFile(QString path, bool isPrivate);
    void init();
    void sendMessage(QString text);

    void requestFileList();
signals:
    void responseFileList(QStringList, QStringList);
    void connectSender();
    void connectReceiver();
    void sendFileSignal(QString path, bool isPrivate);
    void messageReceived(QByteArray msg);
    void fileReceived(QString path);
};
#endif // CLIENT_H
