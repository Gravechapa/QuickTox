#include "maincontroller.h"
#include "toxmodel.h"
#include <QDebug>

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
    getToxModel().send_message(msg.toStdString());
}
