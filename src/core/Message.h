#ifndef MESSAGE_H
#define MESSAGE_H
#include <tox/tox.h>
#include <string>

class Message
{
private:
    uint32_t _friend_number;
    TOX_MESSAGE_TYPE _type;
    std::string _msg;
    uint32_t _chat_id;
public:
    Message(uint32_t friend_number_, TOX_MESSAGE_TYPE type_, std::string msg_, uint32_t chat_id_);

    uint32_t friend_number() const;

    TOX_MESSAGE_TYPE type() const;

    std::string msg() const;

    uint32_t chat_id() const;
};

#endif // MESSAGE_H
