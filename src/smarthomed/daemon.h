#ifndef DAEMON_H
#define DAEMON_H

#include <QObject>

QT_BEGIN_NAMESPACE
class QHostAddress;
class QMutex;
class QSocketNotifier;
QT_END_NAMESPACE

class HomeController;
class Server;
class QCron;

class Daemon : public QObject
{
    Q_OBJECT
public:
    static Daemon &instance() {
        static Daemon instance;
        return instance;
    }

    static void qtMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg);

    int start();
    int runInTerminal();

private:
    quint16 m_serverPort;
    HomeController *m_homeController;
    Server *m_server;
    QCron *m_cron;

    explicit Daemon(QObject *parent = 0);

    void init();
    void run();
    void stop();

    // Unix signal handler
    static void hupSignalHandler(int unused);
    static void termSignalHandler(int unused);

public slots:
    // Qt signal handlers.
    void handleSigHup();
    void handleSigTerm();

protected slots:
    void handleSignals();
    void cronJob();

private:
    static int sigHupFd[2];
    static int sigTermFd[2];

    QSocketNotifier *snHup;
    QSocketNotifier *snTerm;

};

#endif // DAEMON_H
