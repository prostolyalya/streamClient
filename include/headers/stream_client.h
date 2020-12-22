#ifndef STREAMCLIENT_H
#define STREAMCLIENT_H
#pragma once

#include "client.h"
#include "ui_controller.h"
#include <QTcpSocket>
#include <QQmlApplicationEngine>
#include "thread_pool.h"
class StreamClient : public QObject
{
    Q_OBJECT
public:
    StreamClient(QQmlApplicationEngine&_engine,QObject *parent = nullptr);
    ~StreamClient();

    std::shared_ptr<UiController> getUiController() const;
    static bool checkClient(QString username, QString password);
public slots:
    void init(QString login, QString pass);
private:
    QQmlApplicationEngine &engine;
    std::unique_ptr<Client> client;
    std::unique_ptr<ThreadPool> thread_pool;
    std::shared_ptr<UiController> uiController;
    const QString host = "192.168.0.102";

signals:
    void initClient();
};

#endif // STREAMCLIENT_H
