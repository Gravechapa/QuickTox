#include "toxmodel.h"
#include "MessageDB.h"
#include "Message.h"

ToxModel::ToxModel()
{
    TOX_ERR_NEW err_new;
    _tox = tox_new(NULL, &err_new);
    if (err_new != TOX_ERR_NEW_OK)
    {
        throw std::runtime_error("Toxcore");
    }
    _finalize = false;

    ToxCallbackHelper::registerModel(this);
}

ToxModel::~ToxModel()
{
    _finalize = true;
    if(_tox_main_loop.joinable())
        {
            _tox_main_loop.join();
        }
    tox_kill(_tox);
}

void ToxModel::ToxCallbackHelper::friend_message_cb_helper(Tox *tox_c, uint32_t friend_number, TOX_MESSAGE_TYPE type, const uint8_t *message,
                                     size_t length, void *user_data)
{
    Message msg(friend_number, type, reinterpret_cast<const char*>(message), 0); //TODO: use Message class, Luke
    getMessageDB().addMsg(msg);
    qDebug() << "Mesage received";
    _toxModel->_lastReceived = friend_number;
    const char *str = reinterpret_cast<const char*>(message);
    _toxModel->_receive_message_callback(friend_number, type, str, user_data);
}

void ToxModel::ToxCallbackHelper::friend_request_cb_helper(Tox *tox_c, const uint8_t *public_key, const uint8_t *message, size_t length, void *user_data)
{
    qDebug() << "Request received";
    tox_friend_add_norequest(tox_c, public_key, NULL);
}

void ToxModel::ToxCallbackHelper::self_connection_status_cb_helper(Tox *tox_c, TOX_CONNECTION connection_status, void *user_data)
{
    qDebug() << "Connection status";
    _toxModel->_self_connection_status = connection_status;
    switch (connection_status)
        {
            case TOX_CONNECTION_NONE:
                _toxModel->_self_connection_status_callback("NONE");
                break;
            case TOX_CONNECTION_TCP:
                _toxModel->_self_connection_status_callback("TCP");
                break;
            case TOX_CONNECTION_UDP:
                _toxModel->_self_connection_status_callback("UDP");
                break;
        }

}

void ToxModel::authenticate(const std::string &username) //TODO: exception handling
{
    auto res = getMessageDB().openDB("test", "test");
    const uint8_t* name = reinterpret_cast<const uint8_t*>(username.c_str());
    if(!tox_self_set_name(_tox, name, std::strlen(username.c_str()), NULL))
    {
        throw std::runtime_error("Cannot set user name");
    }

    const char *status_message = "Hello world";
    if (!tox_self_set_status_message(_tox, reinterpret_cast<const uint8_t*>(status_message), strlen(status_message), NULL))
    {
        throw std::runtime_error("Cannot set status");
    }

    _nodes = get_dht_nodes();

    uint8_t tox_id_bin[TOX_ADDRESS_SIZE];
    tox_self_get_address(_tox, tox_id_bin);

    char tox_id_hex[TOX_ADDRESS_SIZE * 2 + 1];
    sodium_bin2hex(tox_id_hex, sizeof(tox_id_hex), tox_id_bin, sizeof(tox_id_bin));

    for (size_t i = 0; i < sizeof(tox_id_hex) - 1; i ++) {
        tox_id_hex[i] = toupper(tox_id_hex[i]);
    }

    tox_callback_friend_request(_tox, ToxCallbackHelper::friend_request_cb_helper);
    tox_callback_friend_message(_tox, ToxCallbackHelper::friend_message_cb_helper);
    tox_callback_self_connection_status(_tox, ToxCallbackHelper::self_connection_status_cb_helper);

    _tox_main_loop = std::thread(&ToxModel::_tox_loop, this);

    _userid = std::string(tox_id_hex);
    qDebug() << _userid.c_str();
}

void ToxModel::bootstrap()
{
    if (_nodes.size() == 0)
        {
            qCritical() <<"Nodes list is empty!";
        }
    static int rand_value = qrand() % _nodes.size();
    for (int i = 0; i < 2; ++i)
        {
            const DHT_node& node = _nodes[rand_value % _nodes.size()];

            if(node.ip != "-")
                {
                    if(!tox_bootstrap(_tox, node.ip.c_str(), node.port, (uint8_t*)node.key_bin.c_str(), NULL))
                        {
                            qDebug() << "Failed to connect to node: " << node.ip.c_str();
                        }
                    if(!tox_add_tcp_relay(_tox, node.ip.c_str(), node.port, (uint8_t*)node.key_bin.c_str(), NULL))
                        {
                            qDebug() << "Failed to add relay: " << node.ip.c_str();
                        }
                }
            if(node.ipv6 != "-")
                {
                    if(!tox_bootstrap(_tox, node.ipv6.c_str(), node.port, (uint8_t*)node.key_bin.c_str(), NULL))
                        {
                            qDebug() << "Failed to connect to node: " << node.ipv6.c_str();
                        }
                    if(!tox_add_tcp_relay(_tox, node.ipv6.c_str(), node.port, (uint8_t*)node.key_bin.c_str(), NULL))
                        {
                            qDebug() << "Failed to add relay: " << node.ipv6.c_str();
                        }
                }
            ++rand_value;
        }
}

void ToxModel::_tox_loop()
{
    while(!_finalize)
    {
        if(_self_connection_status == TOX_CONNECTION_NONE)
            {
                bootstrap();
            }
        tox_iterate(_tox, NULL);
        //qDebug() << "Iteration succeded";
        std::this_thread::sleep_for(std::chrono::milliseconds(tox_iteration_interval(_tox)));
    }

    qDebug() << "Finalizing";
}

void ToxModel::set_receive_message_callback(std::function<void(uint32_t, TOX_MESSAGE_TYPE, std::string, void *)> callback)
{
    _receive_message_callback = callback;
}

void ToxModel::set_self_connection_status_callback(std::function<void(std::string)> callback)
{
    _self_connection_status_callback = callback;
}

void ToxModel::send_message(std::string &msg)
{ //TODO: error handling
    auto id = tox_friend_send_message(_tox, _lastReceived, TOX_MESSAGE_TYPE_NORMAL, reinterpret_cast<const uint8_t*>(msg.c_str()), msg.size(), NULL);
    auto message = Message(_lastReceived, TOX_MESSAGE_TYPE_NORMAL, msg, id);
    getMessageDB().addMsg(message);
}

std::string &ToxModel::getUserId()
{
    return _userid;
}

ToxModel *ToxModel::ToxCallbackHelper::_toxModel = nullptr;

void ToxModel::ToxCallbackHelper::registerModel(ToxModel *model)
{
    _toxModel = model;
}

void ToxModel::ToxCallbackHelper::unregisterModel()
{
    _toxModel = nullptr;
}

ToxModel& getToxModel()
{
    static ToxModel tox;
    return tox;
}
