#include "db_connector.h"

DBConnector::DBConnector(QString dbName)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbName);
    if (db.open())
    {
        QSqlQuery query;
        query.exec(QString("CREATE TABLE IF NOT EXISTS " + tableName1
                           + " ("
                             "user_id         TEXT , "
                             "user_login      TEXT , "
                             "user_passcode   TEXT ); "));
        query.exec(QString("CREATE TABLE IF NOT EXISTS " + tableName2
                           + " ("
                             "user_id      TEXT, "
                             "video_name   TEXT, "
                             "video_path   TEXT ); "));
        query.exec(QString("CREATE TABLE IF NOT EXISTS " + tableName3
                           + " ("
                             "user_id      TEXT, "
                             "audio_name   TEXT, "
                             "audio_path   TEXT ); "));
        db.close();
    }
    else
    {
        qDebug() << db.lastError().text();
    }
}

bool DBConnector::findUser(QString user_id)
{
    bool find = false;
    if (db.open())
    {
        QSqlQuery query;
        if (query.exec("SELECT user_id FROM my_table WHERE user_id = " + user_id))
        {
            find = true;
        }
        db.close();
    }
    return find;
}

bool DBConnector::addUser(QString user_id, QString login, QString passcode)
{
    bool exec = false;
    if (db.open())
    {
        QString insert = "INSERT INTO users(user_id, user_login, user_passcode) "
                "VALUES ('"
                + user_id+ "', '" + login + "', '" + passcode + "');";
        QSqlQuery query;
        exec = query.exec(insert);

        db.close();
    }
    return exec;
}
