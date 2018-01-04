#include <QCommandLineParser>
#include <QCoreApplication>
#include <QDebug>

#include "common.h"
#include "daemon.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    qRegisterMetaType<Rooms::Room>("Rooms::Room");

    app.setOrganizationName("WaldoCorp");
    app.setOrganizationDomain("waldocorp.tristant.be");
    app.setApplicationName("smarthomed");
    app.setApplicationVersion("0.1.0");

    QCommandLineParser parser;
    parser.setApplicationDescription("Smart Home Daemon");
    parser.addHelpOption();
    parser.addVersionOption();

    // An option with a value
    QCommandLineOption targetStandAloneOption(QStringList() << "exec",
                                             QCoreApplication::translate("main", "launch as standalone."));
    parser.addOption(targetStandAloneOption);


    // Process the actual command line arguments given by the user
    parser.process(app);

    bool standalone = parser.isSet(targetStandAloneOption);

    int ret = 0;
    if (standalone) {
        ret = Daemon::instance().runInTerminal();
    } else {
        qInstallMessageHandler(Daemon::qtMessageOutput);
        ret = Daemon::instance().start();
    }
    return ret;
}
