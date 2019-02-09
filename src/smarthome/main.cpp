#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "common.h"
#include "clientcontroller.h"
#include "data/heatingitem.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    qRegisterMetaType<Rooms::Room>("Rooms::Room");
    qmlRegisterType<Rooms>("RoomsEnums", 1, 0, "Rooms");
    qRegisterMetaType<HeatingItem::HeatingRoles>("HeatingItem::HeatingRoles");
    qmlRegisterType<HeatingItem>("HeatingRolesEnums", 1, 0, "HeatingRoles");


    app.setOrganizationName("JB Tristant");
    app.setOrganizationDomain("tristant.be");
    app.setApplicationDisplayName("Smart Home");
    app.setApplicationName("smarthome");
    app.setApplicationVersion("0.9.0");

    ClientController homeController;
    HeatingListModel heatingListModel(qApp);

    QObject::connect(&homeController, &ClientController::addHeating, &heatingListModel, &HeatingListModel::addHeating);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("homeController", &homeController);
    engine.rootContext()->setContextProperty("heatingListModel", &heatingListModel);
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));


    return app.exec();
}
