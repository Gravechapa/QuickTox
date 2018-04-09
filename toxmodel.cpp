#include "toxmodel.h"
#include <exception>
#include <stdexcept>
#include <sodium.h>
#include <cstring>

ToxModel::ToxModel()
{
    TOX_ERR_NEW err_new;
    tox = tox_new(NULL, &err_new);
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
    _tox_main_loop.join();
    tox_kill(tox);
}

typedef struct DHT_node {
    const char *ip;
    uint16_t port;
    const char key_hex[TOX_PUBLIC_KEY_SIZE*2 + 1]; // 1 for null terminator
    unsigned char key_bin[TOX_PUBLIC_KEY_SIZE];
} DHT_node;

DHT_node nodes[] =
{
    {"178.62.250.138",             33445, "788236D34978D1D5BD822F0A5BEBD2C53C64CC31CD3149350EE27D4D9A2F9B6B", {0}},
    {"2a03:b0c0:2:d0::16:1",       33445, "788236D34978D1D5BD822F0A5BEBD2C53C64CC31CD3149350EE27D4D9A2F9B6B", {0}},
    {"tox.zodiaclabs.org",         33445, "A09162D68618E742FFBCA1C2C70385E6679604B2D80EA6E84AD0996A1AC8A074", {0}},
    {"163.172.136.118",            33445, "2C289F9F37C20D09DA83565588BF496FAB3764853FA38141817A72E3F18ACA0B", {0}},
    {"2001:bc8:4400:2100::1c:50f", 33445, "2C289F9F37C20D09DA83565588BF496FAB3764853FA38141817A72E3F18ACA0B", {0}},
    {"128.199.199.197",            33445, "B05C8869DBB4EDDD308F43C1A974A20A725A36EACCA123862FDE9945BF9D3E09", {0}},
    {"2400:6180:0:d0::17a:a001",   33445, "B05C8869DBB4EDDD308F43C1A974A20A725A36EACCA123862FDE9945BF9D3E09", {0}},
    {"node.tox.biribiri.org",      33445, "F404ABAA1C99A9D37D61AB54898F56793E1DEF8BD46B1038B9D822E8460FAB67", {0}}
};

void ToxModel::ToxCallbackHelper::friend_message_cb_helper(Tox *tox_c, uint32_t friend_number, TOX_MESSAGE_TYPE type, const uint8_t *message,
                                     size_t length, void *user_data)
{
    qDebug() << "Mesage received";
    const char *str = reinterpret_cast<const char*>(message);
    _toxModel->_receive_message_callback(friend_number, type, str, user_data);
}

void ToxModel::ToxCallbackHelper::friend_request_cb_helper(Tox *tox_c, const uint8_t *public_key, const uint8_t *message, size_t length, void *user_data)
{
    qDebug() << "Request received";
    tox_friend_add_norequest(tox_c, public_key, NULL);
}

void ToxModel::authenticate(const std::string &username) //TODO: exception handling
{
    const uint8_t* name = reinterpret_cast<const uint8_t*>(username.c_str());
    if(!tox_self_set_name(tox, name, std::strlen(username.c_str()), NULL))
    {
        throw std::runtime_error("Cannot set user name");
    }

    const char *status_message = "Hello world";
    if (!tox_self_set_status_message(tox, reinterpret_cast<const uint8_t*>(status_message), strlen(status_message), NULL))
    {
        throw std::runtime_error("Cannot set status");
    }

    for (auto i = 0; i < sizeof(nodes)/sizeof(DHT_node); i++)
    {
        sodium_hex2bin(nodes[i].key_bin, sizeof(nodes[i].key_bin),
                       nodes[i].key_hex, sizeof(nodes[i].key_hex)-1, NULL, NULL, NULL);
        tox_bootstrap(tox, nodes[i].ip, nodes[i].port, nodes[i].key_bin, NULL); //TODO: handle false please
    }

    uint8_t tox_id_bin[TOX_ADDRESS_SIZE];
    tox_self_get_address(tox, tox_id_bin);

    char tox_id_hex[TOX_ADDRESS_SIZE*2 + 1];
    sodium_bin2hex(tox_id_hex, sizeof(tox_id_hex), tox_id_bin, sizeof(tox_id_bin));

    for (size_t i = 0; i < sizeof(tox_id_hex)-1; i ++) {
        tox_id_hex[i] = toupper(tox_id_hex[i]);
    }

    tox_callback_friend_request(tox, ToxCallbackHelper::friend_request_cb_helper);
    tox_callback_friend_message(tox, ToxCallbackHelper::friend_message_cb_helper);

    _tox_main_loop = std::thread(&ToxModel::_tox_loop, this);

    _userid = std::string(tox_id_hex);
}

void ToxModel::set_receive_message_callback(std::function<void(uint32_t, TOX_MESSAGE_TYPE, std::string, void *)> callback)
{
    _receive_message_callback = callback;
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

ToxModel TOX_MODEL;

ToxModel& getToxModel()
{
    return TOX_MODEL;
}
