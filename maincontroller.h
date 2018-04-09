#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QObject>

class MainController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString userid READ userid NOTIFY useridChanged)
public:
    explicit MainController(QObject *parent = nullptr);

    ~MainController();

    QString userid();

signals:
    void messageReceived(QString id);
    void useridChanged();

public slots:
};

#endif // MAINCONTROLLER_H
