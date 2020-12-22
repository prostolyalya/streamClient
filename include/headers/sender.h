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

    void connecting(QHostAddress host = QHostAddress::Any);

    void setFile_path(const QString &value);
public slots:
    void readSocket();
    void discardSocket();
    void sendFile();
signals:
    void fileSent(qint64, QString);
private:
    std::unique_ptr<QTcpSocket> socket;
    QString file_path = "";
};
#endif // SENDER_H
