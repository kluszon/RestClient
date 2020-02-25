#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtQml>

#include "source/restclient.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    app.setApplicationName("Rest client");
    app.setApplicationVersion("1.0.0");

    QQmlApplicationEngine engine;

    RestClient *restClient = new RestClient();;

    engine.rootContext()->setContextProperty("restClient", restClient);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
