#include "stream_client.h"

StreamClient::StreamClient(QQmlApplicationEngine& _engine, QObject* parent)
    : QObject(parent)
    , engine(_engine)
{
    uiController = std::make_shared<UiController>();
    connect(uiController.get(), &UiController::login, this, &StreamClient::checkClient);
    connect(uiController.get(), &UiController::registration, this,
            &StreamClient::regClient);
    connect(this, &StreamClient::errorLogin, uiController.get(),
            &UiController::loginError);
    connect(this, &StreamClient::loginComplete, uiController.get(),
            &UiController::registrationComplete);

    uiController->setVideoFilePath(QDir::currentPath() + "/my/tmp");
    address = Authentificate::address;
}

void StreamClient::init()
{
    engine.load(QStringLiteral("qrc:/include/ui/mainClientWindow.qml"));
    client = std::make_unique<Client>(this);
    client->setAddress(address);

    connect(uiController.get(), &UiController::requestFile, client.get(),
            &Client::requestFile, Qt::QueuedConnection);
    connect(uiController.get(), &UiController::requestFileList, client.get(),
            &Client::requestFileList, Qt::QueuedConnection);
    connect(this, &StreamClient::initClient, client.get(), &Client::init,
            Qt::QueuedConnection);
    connect(uiController.get(), &UiController::sendText, client.get(),
            &Client::sendMessage, Qt::QueuedConnection);
    connect(client.get(), &Client::messageReceived, uiController.get(),
            &UiController::addText, Qt::QueuedConnection);
    connect(client.get(), &Client::responseFileList, uiController.get(),
            &UiController::responceFileList, Qt::QueuedConnection);
    connect(uiController.get(), &UiController::sendFile, client.get(), &Client::sendFile,
            Qt::QueuedConnection);
    connect(client.get(), &Client::fileReceived, uiController.get(),
            &UiController::fileReceived, Qt::QueuedConnection);
    ThreadPool::getInstance()->addToThread(this);
    ThreadPool::getInstance()->addToThread(client.get());
//    ThreadPool::getInstance()->addToThread(client.get()->sender.get());

    emit initClient();
}

std::shared_ptr<UiController> StreamClient::getUiController() const
{
    return uiController;
}

void StreamClient::checkClient(QString username, QString password)
{

    auto error = Authentificate::checkLogin(username, password);
    switch (error)
    {
    case Authentificate::Error::NO_ERROR:
        emit loginComplete();
        init();
        break;
    case Authentificate::Error::INCORRECT_LOGIN:
        emit errorLogin("Incorrect login or password");
        break;
    case Authentificate::Error::NAME_USED:
        emit errorLogin("Undefined");
        break;
    case Authentificate::Error::NO_CONNECTION:
        emit errorLogin("Can`t connect to server 0_o, try later");
        break;
    }
}

void StreamClient::regClient(QString username, QString password)
{
    auto error = Authentificate::checkName(username, password);
    switch (error)
    {
    case Authentificate::Error::NO_ERROR:
        emit loginComplete();
        init();
        break;
    case Authentificate::Error::INCORRECT_LOGIN:
        emit errorLogin("Undefined");
        break;
    case Authentificate::Error::NAME_USED:
        emit errorLogin("This name is used, try with Xx_xX");
        break;
    case Authentificate::Error::NO_CONNECTION:
        emit errorLogin("Can`t connect to server 0_o, try later");
        break;
    }
}
