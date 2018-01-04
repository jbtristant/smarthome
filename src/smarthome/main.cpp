#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "common.h"
#include "clientcontroller.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    qRegisterMetaType<Rooms::Room>("Rooms::Room");
    qRegisterMetaType<HeatingState>("HeatingState");
    qmlRegisterType<Rooms>("RoomsEnums", 1, 0, "Rooms");

    app.setOrganizationName("JB Tristant");
    app.setOrganizationDomain("tristant.be");
    app.setApplicationDisplayName("Smart Home");
    app.setApplicationName("smarthome");
    app.setApplicationVersion("0.9.0");

    ClientController homeController;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("homeController", &homeController);
    //engine.rootContext()->setContextProperty("heatingStateModel", QVariant::fromValue(dataList));
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));


    return app.exec();
}
