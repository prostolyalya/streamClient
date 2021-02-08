#include <QGuiApplication>
#include <qqml.h>
#include <QObject>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "stream_client.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    auto client = std::make_unique<StreamClient>(engine);
    engine.rootContext()->setContextProperty("uiController",
                                             client.get()->getUiController().get());
    const QUrl url(QStringLiteral("qrc:/include/ui/startWindow.qml"));
    engine.load(url);
    return app.exec();
}
