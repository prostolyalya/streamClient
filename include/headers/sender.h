#ifndef SENDER_H
#define SENDER_H
#pragma once

#include <QtNetwork>
#include <QObject>

class Sender : public QObject
{
    Q_OBJECT
public:
    Sender(QObject *parent = nullptr);

    void setAddress(const QHostAddress &value);

public slots:
    void connecting();
    void readSocket();
    void discardSocket();
    void sendFile(QString file_path, bool isPrivate);
signals:
    void fileSent(qint64, QString, bool);

private:
    std::unique_ptr<QTcpSocket> socket;
    QHostAddress address;
};
#endif // SENDER_H
