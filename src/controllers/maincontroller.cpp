#include "maincontroller.h"

MainController::MainController(QObject *parent) : QObject(parent)
{
    //TODO: move to proper place
    getToxModel().set_receive_message_callback([this](uint32_t id , TOX_MESSAGE_TYPE type, std::string msg, void *userData)
    {
        auto str = QString::fromUtf8(msg.c_str());
        emit this->messageReceived(str);
    });

    getToxModel().set_self_connection_status_callback([this](std::string status)
    {
        auto str = QString::fromUtf8(status.c_str());
        emit this->statusChanged(str);
    });
    qDebug() << "Constructor called";
}

MainController::~MainController()
{
    getToxModel().set_receive_message_callback([](uint32_t id , TOX_MESSAGE_TYPE type, std::string msg, void *userData) {});
    getToxModel().set_self_connection_status_callback([](std::string status){});
    qDebug() << "Destructor called";
}

QString MainController::userid()
{
    return QString::fromStdString(getToxModel().getUserId());
}

void MainController::sendMsg(QString msg)
{
    auto str = msg.toStdString();
    getToxModel().send_message(str);
}

QStringList MainController::friends()
{
    QStringList friendsL;
    friendsL.append("Hello world!");
    friendsL.append("Nice to meet you!");
    return friendsL;
}
