#include "maincontroller.h"
#include "toxmodel.h"

MainController::MainController(QObject *parent) : QObject(parent)
{
    //TODO: move to proper place
    getToxModel().set_receive_message_callback([this](uint32_t id , TOX_MESSAGE_TYPE type, std::string msg, void *userData)
    {
        auto str = QString::fromUtf8(msg.c_str());
        emit this->messageReceived(str);
    });
}

MainController::~MainController()
{
    getToxModel().set_receive_message_callback([](uint32_t id , TOX_MESSAGE_TYPE type, std::string msg, void *userData) {});
}
