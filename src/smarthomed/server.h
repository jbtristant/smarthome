#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QVector>

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
    void temperatureChanged(double value);
    void humidityChanged(double value);
    void heatChanged(double value);
    void dewChanged(double value);
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
