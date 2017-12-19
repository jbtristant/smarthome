#include <QCoreApplication>
#include <QMutex>
#include <QNetworkAddressEntry>
#include <QSettings>
#include <QTcpServer>
#include <QTcpSocket>
#include <QUdpSocket>

#include "daemon.h"
#include "homecontroller.h"
#include "server.h"

#include "waitsignalhelper.h"

#include <QSocketNotifier>
#include <csignal>
#include <sys/socket.h>
#include <time.h>
#include <unistd.h>

int Daemon::sigHupFd[2];
int Daemon::sigTermFd[2];

Daemon::Daemon(QObject *parent)
    : QObject(parent)
{
}

int Daemon::start()
{
    handleSignals();

    instance().init();

    instance().run();

    int ret = qApp->exec();

    instance().stop();

    return ret;
}

void Daemon::qtMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    Q_UNUSED(context);

    switch(type) {
    case QtDebugMsg:
        fprintf(stderr, "DEBUG: %s\n", msg.toUtf8().data());
        break;
    case QtWarningMsg:
        fprintf(stderr, "WARNING: %s\n", msg.toUtf8().data());
        break;
    case QtCriticalMsg:
        fprintf(stderr, "CRITICAL: %s\n", msg.toUtf8().data());
        break;
    case QtFatalMsg:
        fprintf(stderr, "FATAL: %s\n", msg.toUtf8().data());
        abort();
    }
}

void Daemon::hupSignalHandler(int unused)
{
    Q_UNUSED(unused);

    qDebug() << "signal hup";
    char a = '1';
    if (::write(sigHupFd[0], &a, sizeof(a)) < 0) {
        qWarning() << "signal hup write error occur";
    }
}

void Daemon::termSignalHandler(int unused)
{
    Q_UNUSED(unused);

    qDebug() << "signal term";
    char a = '2';
    if (::write(sigTermFd[0], &a, sizeof(a)) < 0) {
        qWarning() << "signal term write error occur";
    }
}

void Daemon::handleSigHup()
{
    snHup->setEnabled(false);
    char tmp;
    if (::read(sigHupFd[1], &tmp, sizeof(tmp)) < 0) {
        qWarning() << "Signal hup read error occur";
    }

    // do Qt stuff here
    qDebug() << "Signal hup";

    snHup->setEnabled(true);
}

void Daemon::handleSigTerm()
{
    snTerm->setEnabled(false);
    char tmp;
    if (::read(sigTermFd[1], &tmp, sizeof(tmp)) < 0) {
        qWarning() << "Signal term read error";
    }

    qDebug() << "Signal term";
    // Quit the app
    qApp->quit();


    snTerm->setEnabled(true);
}

void Daemon::handleSignals()
{
    int mypid = getpid();
    struct sigaction hup, term;

    // configure les handlers pour les signaux
    hup.sa_handler = Daemon::hupSignalHandler;
    sigemptyset(&hup.sa_mask);
    hup.sa_flags = 0;
    hup.sa_flags |= SA_RESTART;

    if (sigaction(SIGHUP, &hup, 0) > 0)
        return;

    qDebug("SIGHUP; kill -%d %d", SIGHUP, mypid);

    term.sa_handler = Daemon::termSignalHandler;
    sigemptyset(&term.sa_mask);
    term.sa_flags |= SA_RESTART;

    if (sigaction(SIGTERM, &term, 0) > 0)
        return;

    qDebug("SIGTERM; kill -%d %d", SIGTERM, mypid);


    if (::socketpair(AF_UNIX, SOCK_STREAM, 0, sigHupFd)) qFatal("Couldn't create HUP socketpair");
    if (::socketpair(AF_UNIX, SOCK_STREAM, 0, sigTermFd)) qFatal("Couldn't create TERM socketpair");
    snHup = new QSocketNotifier(sigHupFd[1], QSocketNotifier::Read, this);
    connect(snHup, SIGNAL(activated(int)), this, SLOT(handleSigHup()));
    snTerm = new QSocketNotifier(sigTermFd[1], QSocketNotifier::Read, this);
    connect(snTerm, SIGNAL(activated(int)), this, SLOT(handleSigTerm()));
}

int Daemon::runInTerminal()
{
    handleSignals();

    init();
    run();
    int ret = qApp->exec();
    stop();
    return ret;
}

void Daemon::init()
{
    qInfo() << "Init" << qApp->applicationName() << "version" << qApp->applicationVersion();
    QSettings settings(QSettings::SystemScope, qApp->organizationName(), qApp->applicationName(), this);
    if (!settings.contains("port")) settings.setValue("port", 4817);
    m_serverPort = settings.value("port", 4817).toInt();
}

void Daemon::run()
{
    qInfo() << "Run" << qApp->applicationName();
    m_server = new Server(this);
    m_homeController = new HomeController(this);

    if (m_server->listen(QHostAddress::Any, m_serverPort)) {
        qInfo() << "Server listenning on any address with port:" << m_server->serverPort();
        // INPUT
        connect(snHup, &QSocketNotifier::activated, m_server, &Server::handleSigHup);

        // DROWSILOGIC TO SERVER
        connect(m_homeController, &HomeController::temperatureChanged, m_server, &Server::temperatureChanged);
        connect(m_homeController, &HomeController::humidityChanged, m_server, &Server::humidityChanged);
        connect(m_homeController, &HomeController::heatChanged, m_server, &Server::heatChanged);
        connect(m_homeController, &HomeController::dewChanged, m_server, &Server::dewChanged);
        connect(m_homeController, &HomeController::relayChanged, m_server, &Server::relayChanged);

        // SERVER TO DROWSILOGIC
        connect(m_server, &Server::setRelay, m_homeController, &HomeController::setRelay);

    } else {
        qFatal(QString("Server failed to listen with error: \"%1\" on %2 port %3").arg(m_server->errorString())
                 .arg(m_server->serverAddress().toString())
                 .arg(m_server->serverPort()).toUtf8().data());
    }

}

void Daemon::stop()
{
    qInfo() << "Stop" << qApp->applicationName();
    m_server->disconnectedClients();
    m_server->close();
    m_homeController->close();
}
