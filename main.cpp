#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <tox/tox.h>

#include "logincontroller.h"
#include "maincontroller.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegisterType<LoginController>("qatox.LoginController", 1, 0, "LoginController");
    qmlRegisterType<MainController>("qatox.MainController", 1, 0, "MainController");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/LoginWindow.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
