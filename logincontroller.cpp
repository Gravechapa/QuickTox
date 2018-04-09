#include "logincontroller.h"
#include <QDebug>

LoginController::LoginController(QObject *parent) : QObject(parent)
{
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

QString LoginController::authenticate() //TODO: return bool or better invoke signal
{
    return QString::fromUtf8(model.authenticate(m_userName.toUtf8().constData()).c_str());
}
