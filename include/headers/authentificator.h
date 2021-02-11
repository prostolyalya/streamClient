#ifndef AUTHENTIFICATOR_H
#define AUTHENTIFICATOR_H
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
}

#endif // AUTHENTIFICATOR_H
