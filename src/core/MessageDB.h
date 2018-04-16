#pragma once
#include <QSqlDatabase>
#include <QString>
#include <QStandardPaths>
#include "Message.h"

class MessageDB
{
public:
    MessageDB();
    bool openDB(QString name, QString password);

    void addMsg(Message &message);

private:

    QSqlDatabase _db;

};

MessageDB& getMessageDB();
