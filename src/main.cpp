#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <tox/tox.h>

#include "controllers/logincontroller.h"
#include "controllers/maincontroller.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegisterType<LoginController>("QuickTox.LoginController", 1, 0, "LoginController");
    qmlRegisterType<MainController>("QuickTox.MainController", 1, 0, "MainController");

    QQmlApplicationEngine engine;
    engine.load(":/qml/main.qml");
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
