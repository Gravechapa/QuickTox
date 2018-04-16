#pragma once
#include <QSqlDatabase>
#include <QString>
#include <QStandardPaths>

class MessageDB
{
public:
    MessageDB();
    bool openDB(QString name, QString password);

private:

    QSqlDatabase _db;

};

MessageDB& getMessageDB();
