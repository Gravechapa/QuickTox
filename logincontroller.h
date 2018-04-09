#ifndef LOGINCONTROLLER_H
#define LOGINCONTROLLER_H

#include <QObject>

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
    void userAuthenticated();

private:
    QString m_userName;

public slots:

};

#endif // LOGINCONTROLLER_H
