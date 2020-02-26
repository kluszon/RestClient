#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtQml>

#include "source/guiengine.h"
#include "source/requestbodymodel.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    app.setApplicationName("Rest client");
    app.setApplicationVersion("1.0.0");

    QQmlApplicationEngine engine;

    GuiEngine *guiEngine = GuiEngine::getInstance();
    RequestBodyModel *requestBodyModel = RequestBodyModel::getInstance();

    engine.rootContext()->setContextProperty("guiEngine", guiEngine);
    engine.rootContext()->setContextProperty("requestBodyModel", requestBodyModel);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
