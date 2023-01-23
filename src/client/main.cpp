#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QThreadPool>

#include "testclient.h"


int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

//    QThreadPool::globalInstance()->setMaxThreadCount(8);
    auto channel = grpc::CreateChannel("0.0.0.0:50051", grpc::InsecureChannelCredentials());
    TestClient testClient(channel);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("testClient", &testClient);
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
