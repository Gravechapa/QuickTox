#include "MessageDB.h"
#include <QSqlQuery>
#include <QDebug>
#include <QVariant>
#include <QSqlError>
#include <QDateTime>

MessageDB::MessageDB()
{
}

bool MessageDB::openDB(QString name, QString password)
{
    _db = QSqlDatabase::addDatabase("QSQLITE");
    _db.setDatabaseName(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) +
                        "/" + name + ".db");
    _db.setUserName(name);
    _db.setPassword(password);
    auto opened = _db.open();
    QSqlQuery query(_db);
    QString queryCrt = "CREATE TABLE IF NOT EXISTS messages ("
                       "TIME       INTEGER NOT NULL,"
                       "CHAT_ID    INTEGER NOT NULL,"
                       "TYPE       INTEGER NOT NULL,"
                       "FRIEND_ID  INTEGER NOT NULL,"
                       "MESSAGE    TEXT,"
                       "PRIMARY KEY(TIME)"
                       ");";

    QString queryCrt1 = "CREATE TABLE IF NOT EXISTS friends ("
                        "ID         INTEGER NOT NULL,"
                        "PUBLIC_KEY TEXT NOT NULL,"
                        "NAME       TEXT NULL,"
                        "PRIMARY KEY(ID)"
                        ");";

    if(!query.exec(queryCrt))
    {
        qDebug() << query.lastError();
    }
    if(!query.exec(queryCrt1))
    {
        qDebug() << query.lastError();
    }
    return opened;
}

void MessageDB::addMsg(Message &message)
{
    QSqlQuery query(_db);
    query.prepare("INSERT INTO messages (TIME, CHAT_ID, TYPE, FRIEND_ID, MESSAGE)"
                  "VALUES (:time, :chat_id, :type, :friend, :message);");
    query.bindValue(":time", QDateTime::currentSecsSinceEpoch());
    query.bindValue(":chat_id", message.chat_id());
    query.bindValue(":type", message.type());
    query.bindValue(":friend", message.friend_number());
    query.bindValue(":message", message.msg().c_str());
    if(!query.exec())
    {
        qDebug() << query.lastError();
    };
}

void MessageDB::addFriend(uint32_t id, QString public_key)
{
    QSqlQuery query(_db);
    query.prepare("INSERT INTO friends (ID, PUBLIC_KEY)"
                  "VALUES (:id, :public_key);");
    query.bindValue(":id", id);
    query.bindValue(":public_key", public_key);
    if(!query.exec())
    {
        qDebug() << query.lastError();
    };
}

void MessageDB::setFriendName(uint32_t id, QString name)
{
    QSqlQuery query(_db);
    query.prepare("UPDATE friends SET NAME = :name "
                  "WHERE ID = :id;");
    query.bindValue(":name", name);
    query.bindValue(":id", id);
    if(!query.exec())
    {
        qDebug() << query.lastError();
    };
}

MessageDB& getMessageDB()
{
    static MessageDB db;
    return db;
}
