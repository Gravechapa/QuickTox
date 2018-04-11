#ifndef LOGINCONTROLLER_H
#define LOGINCONTROLLER_H

#include <QObject>
#include <QDebug>
#include "../core/toxmodel.h"

class LoginController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString userName READ userName WRITE setUserName NOTIFY userNameChanged)
public:
    explicit LoginController(QObject *parent = nullptr);

    ~LoginController();

    QString userName();
    void setUserName(const QString &userName);

    Q_INVOKABLE void authenticate();

signals:
    void userNameChanged();

private:
    QString m_userName;

public slots:

};

#endif // LOGINCONTROLLER_H
