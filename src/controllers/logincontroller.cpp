#include "logincontroller.h"

LoginController::LoginController(QObject *parent) : QObject(parent)
{
    qDebug() << "LoginController: Constructor called";
}

LoginController::~LoginController()
{
    qDebug() << "LoginController: Destructor called";
}

QString LoginController::userName()
{
    return m_userName;
}

void LoginController::setUserName(const QString &userName)
{
    if (userName == m_userName)
        return;

    m_userName = userName;
    emit userNameChanged();
}

void LoginController::authenticate() //TODO: return bool or better invoke signal
{
    getToxModel().authenticate(m_userName.toUtf8().constData());
}
