#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "tcplink.h"
#include<boost/asio.hpp>


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    boost::asio::io_context ioc;
    TCPLink tcpLink(ioc);
    engine.rootContext()->setContextProperty("TcpLink", &tcpLink);

    engine.loadFromModule("inputcmdtest", "Main");

    return app.exec();
}
