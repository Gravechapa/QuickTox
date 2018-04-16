#include "MessageDB.h"
#include <QSqlQuery>
#include <QDebug>
#include <QVariant>
#include <QSqlError>

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
                       "ID         INTEGER NOT NULL,"
                       "MESSAGE_ID INTEGER NULL,"
                       "TYPE       INTEGER NOT NULL,"
                       "FRIEND_ID  INTEGER NOT NULL,"
                       "MESSAGE    TEXT,"
                       "PRIMARY KEY(ID)"
                       ");";
    if(!query.exec(queryCrt))
    {
        qDebug() << query.lastError();
    }
    return opened;
}

void MessageDB::addMsg(Message &message)
{
    QSqlQuery query(_db);
    query.prepare("INSERT INTO messages (TYPE, FRIEND_ID, MESSAGE)"
                  "VALUES (:type, :friend, :message);");
    query.bindValue(":type", message.type());
    query.bindValue(":friend", message.friend_number());
    query.bindValue(":message", message.msg().c_str());
    query.exec();
}

MessageDB& getMessageDB()
{
    static MessageDB db;
    return db;
}
