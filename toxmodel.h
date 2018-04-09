#ifndef TOXMODEL_H
#define TOXMODEL_H

#include <tox/tox.h>
#include <exception>
#include <string>
#include <functional>
#include <atomic>
#include <thread>
#include <mutex>

#include <QDebug>

class ToxModel
{
public:
    ToxModel();

    ~ToxModel();

    void authenticate(const std::string &username);

    void set_receive_message_callback(std::function<void(uint32_t, TOX_MESSAGE_TYPE, std::string, void *)> callback);

    std::string& getUserId();

private:
    Tox *tox;

    std::function<void(uint32_t, TOX_MESSAGE_TYPE, std::string, void *)> _receive_message_callback;

    std::atomic_bool _finalize;

    std::string _userid;

    class ToxCallbackHelper
    {
    public:
        static void friend_message_cb_helper(Tox *tox_c, uint32_t friend_number, TOX_MESSAGE_TYPE type, const uint8_t *message,
                                             size_t length, void *user_data);

        static void friend_request_cb_helper(Tox *tox_c, const uint8_t *public_key, const uint8_t *message, size_t length, void *user_data);


        static void registerModel(ToxModel *model);

        static void unregisterModel();

    private:
        static ToxModel *_toxModel;
    };

    std::thread _tox_main_loop;

    //std::mutex _tox_mutex;

    void _tox_loop()
    {
        while(!_finalize)
        {
            //_tox_mutex.lock();
            tox_iterate(tox, NULL);
            //_tox_mutex.unlock();
            //qDebug() << "Iteration succeded";
            std::this_thread::sleep_for(std::chrono::milliseconds(tox_iteration_interval(tox)));
        }

        qDebug() << "Finalizing";
    }
};

ToxModel& getToxModel();

#endif // TOXMODEL_H
