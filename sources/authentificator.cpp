#include "authentificator.h"

#include <QHostAddress>
#include <QTcpSocket>

Authentificate::Error Authentificate::checkName(QString username, QString password)
{
    QTcpSocket socket;
    socket.connectToHost(QHostAddress::LocalHost, 6003);
    socket.waitForConnected(3000);
    if (socket.state() == QTcpSocket::ConnectedState)
    {
        qDebug() << "connect reg ok";
    }
    else
    {
        return Authentificate::Error::NO_CONNECTION;
    }
    const char* data =
        "registration_user/" + username.toLatin1() + "/" + password.toLatin1();
    socket.write(data);
    while (socket.waitForBytesWritten(100)) { }
    while (!socket.waitForReadyRead()) { }
    QByteArray receive_data = socket.readAll();
    if (receive_data == "registration_ok")
    {
        return Authentificate::Error::NO_ERROR;
    }
    else
    {
        return Authentificate::Error::NAME_USED;
    }
}

Authentificate::Error Authentificate::checkLogin(QString username, QString password)
{
    QTcpSocket socket;
    socket.connectToHost(QHostAddress::LocalHost, 6003);
    socket.waitForConnected(3000);
    if (socket.state() == QTcpSocket::ConnectedState)
    {
        qDebug() << "connect auth ok";
    }
    else
    {
        return Authentificate::Error::NO_CONNECTION;
    }
    const char* data = "login_user/" + username.toLatin1() + "/" + password.toLatin1();
    socket.write(data);
    while (socket.waitForBytesWritten(100)) { }
    while (!socket.waitForReadyRead()) { }
    QByteArray receive_data = socket.readAll();
    if (receive_data == "login_ok")
    {
        return Authentificate::Error::NO_ERROR;
    }
    else
    {
        return Authentificate::Error::INCORRECT_LOGIN;
    }
}
