#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <tox/tox.h>

#include "backend.h"
#include "logincontroller.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegisterType<LoginController>("qatox.LoginController", 1, 0, "LoginController");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/LoginWindow.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
