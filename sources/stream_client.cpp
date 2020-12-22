#include "stream_client.h"

StreamClient::StreamClient(QQmlApplicationEngine &_engine, QObject *parent)
    : QObject(parent)
    , engine(_engine)
{
    thread_pool = std::make_unique<ThreadPool>();
    uiController = std::make_shared<UiController>();
    connect(uiController.get(), &UiController::init, this, &StreamClient::init);
}

StreamClient::~StreamClient()
{
}

void StreamClient::init(QString login, QString pass)
{
    engine.load(QStringLiteral("qrc:/include/ui/mainClientWindow.qml"));
    client = std::make_unique<Client>(0);
    connect(this, &StreamClient::initClient, client.get(), &Client::init, Qt::QueuedConnection);
    connect(uiController.get(), &UiController::sendText, client.get(), &Client::sendMessage,
            Qt::QueuedConnection);
    connect(client.get(), &Client::messageReceived, uiController.get(), &UiController::addText,
            Qt::QueuedConnection);
    connect(uiController.get(), &UiController::sendFile, client.get(), &Client::sendFile,
            Qt::QueuedConnection);
    ThreadPool::getInstance()->addToThread(this);
    ThreadPool::getInstance()->addToThread(client.get());
    ThreadPool::getInstance()->addToThread(client.get()->sender.get());

    emit initClient();
}

std::shared_ptr<UiController> StreamClient::getUiController() const
{
    return uiController;
}

bool StreamClient::checkClient(QString username, QString password)
{
    return true;
}
