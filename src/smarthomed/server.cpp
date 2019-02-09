#include "client.h"
#include "server.h"

Server::Server(QObject *parent) : QTcpServer(parent)
{

}

void Server::disconnectedClients()
{
    qInfo() << "Server disconnected clients";
    foreach (Client *client, m_clients) {
        deleteClient(client);
    }
}

Server::~Server()
{
    qInfo() << "Server destruction";
    disconnectedClients();
}

void Server::incomingConnection(qintptr socketDescriptor)
{
    qInfo() << "Server incoming Connection";
    Client *client = new Client(socketDescriptor, this);
    connect(client, &Client::disconnected, this, &Server::clientDisconnected);

    // INPUT
    connect(this, &Server::handleSigHup, client, &Client::handleSigHup);
    connect(this, &Server::temperatureChanged, client, &Client::temperatureChanged);
    connect(this, &Server::humidityChanged, client, &Client::humidityChanged);
    connect(this, &Server::heatChanged, client, &Client::heatChanged);
    connect(this, &Server::dewChanged, client, &Client::dewChanged);
    connect(this, &Server::relayChanged, client, &Client::relayChanged);
    connect(this, &Server::sendHeatingStateList, client, &Client::sendHeatingStateList);
    connect(this, &Server::heatingStateChanged, client, &Client::heatingStateChanged);

    // OUTPUT
    connect(client, &Client::setRelay, this, &Server::setRelay);
    connect(client, &Client::askHeatingStateList, this, &Server::askHeatingStateList);
    connect(client, &Client::setHeatingState, this, &Server::setHeatingState);

    m_clients.append(client);
}

void Server::clientDisconnected()
{
    qInfo() << "Server client disconnected";
    deleteClient((Client *)sender());
}

void Server::deleteClient(Client *client)
{
    qInfo() << "Server delete client";
    int index = m_clients.indexOf(client);
    if (index != -1) m_clients.removeAt(index);
    delete client;
}
