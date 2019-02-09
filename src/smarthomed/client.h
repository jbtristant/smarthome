#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QThread>

#include "common.h"

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(int socketDescriptor, QObject *parent = nullptr);
    ~Client();

signals:
    // INPUT
    void write(QByteArray data);
    void handleSigHup();

    void temperatureChanged(Rooms::Room room, double value);
    void humidityChanged(Rooms::Room room, double value);
    void heatChanged(Rooms::Room room, double value);
    void dewChanged(Rooms::Room room, double value);
    void relayChanged(int card, int relay, bool relayState);
    void sendHeatingStateList(const QString &serializedList);
    void heatingStateChanged(const QString &id);


    // OUTPUT
    void disconnected();
    void error(QTcpSocket::SocketError socketError);

    void setRelay(int card, int relay, bool state);
    void askHeatingStateList();
    void setHeatingState(const QString &id);

private:
    QThread m_workerThread;

};

class ClientWorker : public QObject
{
 Q_OBJECT
public:
    explicit ClientWorker(int socketDescriptor, QObject *parent = nullptr);
    ~ClientWorker();

signals:
    void disconnected();
    void error(QTcpSocket::SocketError socketError);

    // 1.0
    void setRelay(int card, int relay, bool state);
    void askHeatingStateList();
    void setHeatingState(const QString &id);

public slots:
    void init();
    void write(QByteArray data);
    void handleSigHup();

    // 1.0
    void temperatureChanged(Rooms::Room room, double value);
    void humidityChanged(Rooms::Room room, double value);
    void heatChanged(Rooms::Room room, double value);
    void dewChanged(Rooms::Room room, double value);
    void relayChanged(int card, int relay, bool relayState);
    void sendHeatingStateList(const QString &serializedList);
    void heatingStateChanged(const QString &id);

private slots:
    void readyRead();
    void close();

    void parse_1_0(const QByteArray &data);

protected:
    int m_socketDescriptor;
    QTcpSocket *m_socket;

    int m_majorVersion;
    int m_minorVersion;
};


#endif // CLIENT_H
