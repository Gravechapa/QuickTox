#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QStandardPaths>
#include <QDir>
#include <tox/tox.h>

#include "controllers/logincontroller.h"
#include "controllers/maincontroller.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setApplicationName("QuickTox");

    QString data_path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QString config_path = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);
    QDir dir(data_path);
    if (!dir.exists())
        {
            dir.mkpath(data_path);
        }
    dir.setPath(config_path);
    if (!dir.exists())
        {
            dir.mkpath(config_path);
        }
    QFile::copy(":/configs/nodes.json", config_path + "/nodes.json");

    QGuiApplication app(argc, argv);

    qmlRegisterType<LoginController>("QuickTox.LoginController", 1, 0, "LoginController");
    qmlRegisterType<MainController>("QuickTox.MainController", 1, 0, "MainController");

    QQmlApplicationEngine engine;
    engine.load(":/qml/main.qml");
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
