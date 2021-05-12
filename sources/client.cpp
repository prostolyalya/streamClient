#include "client.h"
#include "thread_pool.h"
#include "serializer.h"

Client::Client(QObject *parent)
    : QObject(parent)
{
    socket = std::make_unique<QTcpSocket>(this);
    current_path = QDir::currentPath() + "/my/";
    QDir().mkdir(current_path);
    connect(socket.get(), &QTcpSocket::readyRead, this, &Client::slotRead);
    connect(socket.get(), &QTcpSocket::disconnected, this, &Client::slotServerDisconnected);
    sender = std::make_unique<Sender>(this);
    receiver = std::make_unique<Receiver>(current_path + "tmp", this);
    connect(sender.get(), &Sender::fileSent, this, &Client::fileSent, Qt::QueuedConnection);
    connect(this, &Client::sendFileSignal, sender.get(), &Sender::sendFile, Qt::QueuedConnection);
    connect(this, &Client::connectSender, sender.get(), &Sender::connecting, Qt::QueuedConnection);
    connect(this, &Client::connectReceiver, receiver.get(), &Receiver::connecting, Qt::QueuedConnection);
}

void Client::setAddress(const QHostAddress &value)
{
    address = value;
    sender->setAddress(value);
    receiver->setAddress(value);
}

void Client::sendMessage(QString text)
{
    socket->write(text.toUtf8());
}

void Client::saveFile()
{
    if (sizeFile < receiver.get()->file_size)
        QTimer::singleShot(3000, this, &Client::saveFile);
    else
    {
        while (QFile(current_path + fileName).exists())
            fileName.push_front("1");
        QFile file(current_path + "tmp");
        if (file.size() < sizeFile)
        {
            QTimer::singleShot(3000, this, &Client::saveFile);
            return;
        }
        if (file.open(QFile::ReadOnly))
        {
            QFile::copy(current_path + "tmp", current_path + fileName);
            emit messageReceived("File received: " + current_path.toUtf8() + fileName.toUtf8());
            emit fileReceived(current_path.toUtf8() + fileName.toUtf8());
        }
        else
        {
            emit messageReceived("Error receive file!");
        }
        file.close();
        receiver->file_size = 0;
        receiver.get()->clearTmpFile();
        sizeFile = 0;
    }
}

void Client::connecting()
{
    socket->connectToHost(address, 6000);
    socket->waitForConnected(2000);
    if (socket->state() == QTcpSocket::ConnectedState)
    {
        if (!receiver || !sender)
            return;
        emit connectSender();
        emit connectReceiver();
        if (receiver.get()->socketState() == QTcpSocket::ConnectedState
            && sender.get()->socketState() == QTcpSocket::ConnectedState)
        {
            emit messageReceived("Connected to server");
            requestFileList();
            return;
        }
    }
    emit messageReceived("Can`t connect to server, reconnecting...");
    QTimer::singleShot(3000, this, &Client::connecting);
}

void Client::init()
{
    connecting();
}

void Client::slotRead()
{
    while (socket->bytesAvailable() > 0)
    {
        QByteArray array = socket->readAll();
        if (array.startsWith("end_of_file"))
        {
            qDebug() << "end of file";
            QByteArrayList list = array.split('/');
            QByteArray data = list.at(1);
            fileName = list.at(2);
            sizeFile = data.toInt();
            QTimer::singleShot(1000, this, &Client::saveFile);
        }
        else if (array.startsWith("response_list_file"))
        {
            QString names = array;
            QStringList list = names.split("//");
            QStringList data_priv = Serialize::deserialize(list.at(1));
            QStringList data_pub = Serialize::deserialize(list.at(2));
            emit responseFileList(data_priv, data_pub);
        }
        else
            emit messageReceived("From server:" + array);
    }
}

void Client::requestFile(QString file_name)
{
    QByteArray data = "request_file/" + file_name.toUtf8();
    socket->write(data);
}

void Client::slotServerDisconnected()
{
    emit messageReceived("Failed connect to server, reconnecting...");
    socket->reset();
    connecting();
}

void Client::fileSent(qint64 size, QString fileName, bool isPrivate)
{
    char priv = isPrivate ? '1' : '0';
    socket->write("end_of_file/" + QByteArray::number(size) + "/" + fileName.toUtf8() + "/" + priv);
    emit messageReceived("File sent: " + fileName.toUtf8());
    QTimer::singleShot(1000, this, &Client::requestFileList);
}

void Client::sendFile(QString path, bool isPrivate)
{
    path = path.mid(7);
    emit messageReceived("Send file: " + path.toUtf8());
    emit sendFileSignal(path, isPrivate);
    //    auto f = std::bind(&Sender::sendFileSignal, sender.get());
    //    ThreadPool::getInstance()->addToThread(f);
}

void Client::requestFileList()
{
    QTimer::singleShot(1000, this, [this]() { sendMessage("request_list_file"); });
}
