#ifndef STREAMCLIENT_H
#define STREAMCLIENT_H
#pragma once

#include "client.h"
#include "ui_controller.h"
#include <QTcpSocket>
#include <QQmlApplicationEngine>
#include "authentificator.h"
#include "thread_pool.h"
class StreamClient : public QObject
{
    Q_OBJECT
public:
    StreamClient(QQmlApplicationEngine&_engine,QObject *parent = nullptr);
    ~StreamClient();

    std::shared_ptr<UiController> getUiController() const;

public slots:
    void checkClient(QString username, QString password);
    void regClient(QString username, QString password);
private:
    QQmlApplicationEngine &engine;
    std::unique_ptr<Client> client;
    std::unique_ptr<ThreadPool> thread_pool;
    std::shared_ptr<UiController> uiController;

    void init();
signals:
    void initClient();
    void loginComplete();
    void errorLogin(QString error);
};

#endif // STREAMCLIENT_H
