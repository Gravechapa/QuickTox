#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <tox/tox.h>
#include <exception>

int main(int argc, char *argv[])
{
    TOX_ERR_NEW err_new;
    Tox *tox = tox_new(NULL, &err_new);
    if (err_new != TOX_ERR_NEW_OK)
        {
            throw std::runtime_error("Toxcore");
        }
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
