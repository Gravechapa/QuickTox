#include "MessageDB.h"

MessageDB::MessageDB()
{
}

bool MessageDB::openDB(QString name, QString password)
{
    _db = QSqlDatabase::addDatabase("QSQLITE");
    _db.setDatabaseName(QStandardPaths::writableLocation(QStandardPaths::DataLocation) +
                        "/" + name + ".db");
    _db.setUserName(name);
    _db.setPassword(password);
    return _db.open();
}

MessageDB MESSAGE_DB;

MessageDB& getMessageDB()
{
    return MESSAGE_DB;
}
