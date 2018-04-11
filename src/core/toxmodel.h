#ifndef TOXMODEL_H
#define TOXMODEL_H

#include <tox/tox.h>
#include <exception>
#include <string>
#include <functional>
#include <atomic>
#include <thread>
#include <mutex>
#include <stdexcept>
#include <cstring>
#include <QDebug>
#include <sodium.h>
#include "../configs/NodesParser.h"

class ToxModel
{
public:
    ToxModel();

    ~ToxModel();

    void authenticate(const std::string &username);
    void bootstrap();

    void set_receive_message_callback(std::function<void(uint32_t, TOX_MESSAGE_TYPE, std::string, void *)> callback);
    void set_self_connection_status_callback(std::function<void(std::string)> callback);

    void send_message(std::string &msg);

    std::string& getUserId();

private:
    Tox *_tox;

    uint8_t _self_connection_status = TOX_CONNECTION_NONE;

    std::function<void(uint32_t, TOX_MESSAGE_TYPE, std::string, void *)> _receive_message_callback;
    std::function<void(std::string)> _self_connection_status_callback;

    std::atomic_bool _finalize;

    std::string _userid;

    uint32_t _lastReceived;//TODO: remove it and move to some class of friends;

    std::vector<DHT_node> _nodes;

    class ToxCallbackHelper
    {
    public:
        static void friend_message_cb_helper(Tox *tox_c, uint32_t friend_number, TOX_MESSAGE_TYPE type, const uint8_t *message,
                                             size_t length, void *user_data);

        static void friend_request_cb_helper(Tox *tox_c, const uint8_t *public_key, const uint8_t *message, size_t length, void *user_data);

        static void self_connection_status_cb_helper(Tox *tox_c, TOX_CONNECTION connection_status, void *user_data);

        static void registerModel(ToxModel *model);

        static void unregisterModel();

    private:
        static ToxModel *_toxModel;
    };

    std::thread _tox_main_loop;

    void _tox_loop();
};

ToxModel& getToxModel();

#endif // TOXMODEL_H
