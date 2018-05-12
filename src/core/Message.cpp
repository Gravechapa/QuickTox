#include "Message.h"

Message::Message(uint32_t friend_number_, TOX_MESSAGE_TYPE type_, std::string msg_, uint32_t msg_id_)
{
    _friend_number = friend_number_;
    _type = type_;
    _msg = msg_;
    _msg_id = msg_id_;
}

//TODO: add function to create msg instance by id from db

uint32_t Message::friend_number() const
{
    return _friend_number;
}

TOX_MESSAGE_TYPE Message::type() const
{
    return _type;
}

std::string Message::msg() const
{
    return _msg;
}

uint32_t Message::msg_id() const
{
    return _msg_id;
}
