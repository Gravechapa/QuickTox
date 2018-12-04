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
    void addFriend(uint32_t id, QString public_key);
    void setFriendName(uint32_t id, QString name);

private:

    QSqlDatabase _db;

};

MessageDB& getMessageDB();
