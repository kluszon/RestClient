#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtQml>

#include "source/restclient.h"
#include "source/requestbodymodel.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    app.setApplicationName("Rest client");
    app.setApplicationVersion("1.0.0");

    QQmlApplicationEngine engine;

    RestClient *restClient = new RestClient();
    RequestBodyModel *requestBodyModel = RequestBodyModel::getInstance();

    engine.rootContext()->setContextProperty("restClient", restClient);
    engine.rootContext()->setContextProperty("requestBodyModel", requestBodyModel);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
