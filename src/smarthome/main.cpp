#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "clientcontroller.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    app.setOrganizationName("JB Tristant");
    app.setOrganizationDomain("tristant.be");
    app.setApplicationDisplayName("Smart Home");
    app.setApplicationName("smarthome");
    app.setApplicationVersion("0.9.0");

    ClientController homeController;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("homeController", &homeController);
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));


    return app.exec();
}
