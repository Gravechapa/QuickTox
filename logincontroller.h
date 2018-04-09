#ifndef LOGINCONTROLLER_H
#define LOGINCONTROLLER_H

#include <QObject>
#include "toxmodel.h"

class LoginController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString userName READ userName WRITE setUserName NOTIFY userNameChanged)
public:
    explicit LoginController(QObject *parent = nullptr);

    QString userName();
    void setUserName(const QString &userName);

    Q_INVOKABLE QString authenticate();

signals:
    void userNameChanged();
    void userAuthenticated();

private:
    QString m_userName;

    ToxModel model;

public slots:

};

#endif // LOGINCONTROLLER_H
