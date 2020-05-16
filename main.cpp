#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQmlComponent>

#include "memory.h"
#include "segment_table_model.h"
#include "memory_model.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegisterType<Memory>("MemoryManagment", 1, 0, "Memory");
    qmlRegisterType<SegmentTableModel>("MemoryManagment", 1, 0, "SegmentTableModel");
    qmlRegisterType<MemoryModel>("MemoryManagment", 1, 0, "MemoryModel");


    QQmlApplicationEngine engine;

    Memory memory;

    QQmlContext qQmlContext  = QQmlContext(engine.rootContext());
    qQmlContext.setContextProperty("memory", &memory);

    const QUrl url(QStringLiteral("qrc:/main.qml"));

    QQmlComponent main(&engine, url);

    main.create(&qQmlContext);

//    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
//                     &app, [url](QObject *obj, const QUrl &objUrl) {
//        if (!obj && url == objUrl)
//            QCoreApplication::exit(-1);
//    }, Qt::QueuedConnection);

//    engine.load(url);

    return app.exec();
}
