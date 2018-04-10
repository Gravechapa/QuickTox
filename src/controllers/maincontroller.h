#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QObject>
#include "../core/toxmodel.h"
#include <QDebug>

class MainController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString userid READ userid NOTIFY useridChanged)
public:
    explicit MainController(QObject *parent = nullptr);

    ~MainController();

    QString userid();

    Q_INVOKABLE void sendMsg(QString msg);

signals:
    void messageReceived(QString id);
    void statusChanged(QString status);
    void useridChanged();

public slots:
};

#endif // MAINCONTROLLER_H
