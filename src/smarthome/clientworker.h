#ifndef CLIENTWORKER_H
#define CLIENTWORKER_H

#include <QObject>
#include <QTcpSocket>

#include "common.h"


class ClientWorker : public QObject
{
    Q_OBJECT
public:
    explicit ClientWorker(QObject *parent = nullptr);
    ~ClientWorker();

signals:
    void temperatureChanged(Rooms::Room room, double value);
    void humidityChanged(Rooms::Room room, double value);
    void heatChanged(Rooms::Room room, double value);
    void dewChanged(Rooms::Room room, double value);
    void relayChanged(int card, int relay, bool relayState);
    void addHeating(const QString &name, const QString &id);
    void heatingStateChanged(const QString &id);

public slots:
    void init();
    void close();
    void setRelay(int card, int relay, bool state);
    void setHeatingState(const QString &id);

protected slots:
    void serverConnected();
    void readyRead();
    void parse(const QByteArray &data);


protected:
    QTcpSocket *m_socket;

};

#endif // CLIENTWORKER_H
