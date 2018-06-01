#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QObject>
#include "../core/toxmodel.h"
#include <QDebug>

class MainController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString userid READ userid NOTIFY useridChanged)
    Q_PROPERTY(QStringList friends READ friends NOTIFY friendsChanged)
public:
    explicit MainController(QObject *parent = nullptr);

    ~MainController();

    QString userid();
    QStringList friends();

    Q_INVOKABLE void sendMsg(QString msg);

signals:
    void messageReceived(QString id);
    void statusChanged(QString status);
    void useridChanged();
    void friendsChanged();

public slots:
};

#endif // MAINCONTROLLER_H
