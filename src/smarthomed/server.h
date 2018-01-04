#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QVector>

#include "common.h"

class Client;

class Server : public QTcpServer
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);
    ~Server();

    void disconnectedClients();

signals:
    void handleSigHup();

    // INPUT
    void temperatureChanged(Rooms::Room room, double value);
    void humidityChanged(Rooms::Room room, double value);
    void heatChanged(Rooms::Room room, double value);
    void dewChanged(Rooms::Room room, double value);
    void relayChanged(int card, int relay, bool relayState);

    // OUTPUT
    void setRelay(int card, int relay, bool state);

protected:
    void incomingConnection(qintptr socketDescriptor) override;

private slots:
    void clientDisconnected();
    void deleteClient(Client *client);

private:
    QVector<Client *> m_clients;
};

#endif // SERVER_H
