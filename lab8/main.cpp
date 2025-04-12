#include <QGuiApplication>
#include <QQmlApplicationEngine>

int main(int argc, char ** const argv)
{
    const QGuiApplication application(argc, argv);

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &application,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection
    );
    engine.loadFromModule("lab8", "Main");

    return QGuiApplication::exec();
}
