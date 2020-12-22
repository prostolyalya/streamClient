#ifndef RECEIVER_H
#define RECEIVER_H
#pragma once
#include <QTcpSocket>
#include <QObject>
#include <QFile>
class Receiver : public QObject
{
    Q_OBJECT
public:
    Receiver(QString path, QObject* parent = nullptr);
    ~Receiver();
    void connecting();
    void clearTmpFile();
    QString tmp_path = "";
    qint64 file_size = 0;
    void setReceiver_socket(QTcpSocket* value);
    std::unique_ptr<QFile> file;
public slots:
    void slotRead();
    void slotDisconnected();

private:
    std::unique_ptr<QTcpSocket> socket;
};
#endif // RECEIVER_H
