#ifndef AUTHENTIFICATOR_H
#define AUTHENTIFICATOR_H
#include <QHostAddress>
#include <QString>
namespace Authentificate {
enum Error {
    NO_ERROR,
    INCORRECT_LOGIN,
    NAME_USED,
    NO_CONNECTION
};
    Error checkName(QString username, QString password);
    Error checkLogin(QString username, QString password);
    const QHostAddress address("192.168.0.106");
}

#endif // AUTHENTIFICATOR_H
