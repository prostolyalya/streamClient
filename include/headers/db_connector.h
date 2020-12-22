#ifndef DB_CONNECTOR_H
#define DB_CONNECTOR_H
#pragma once

#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QDebug>

class DBConnector
{
public:
    DBConnector(QString dbName);
    bool findUser(QString user_id);
    bool addUser(QString user_id, QString login, QString passcode);

private:
    QSqlDatabase db;
    QString tableName1 = "users";
    QString tableName2 = "videos";
    QString tableName3 = "audio";
};

#endif // DB_CONNECTOR_H
