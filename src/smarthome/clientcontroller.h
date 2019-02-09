#ifndef CLIENTCONTROLLER_H
#define CLIENTCONTROLLER_H

#include <QObject>
#include <QThread>

#include "common.h"

class ClientController : public QObject
{
    Q_OBJECT

public:
    explicit ClientController(QObject *parent = nullptr);
    ~ClientController();

signals:
    // INPUT
    void close();
    void setRelay(int card, int relay, bool state);
    void setHeatingState(const QString &id);

    // OUTPUT
    void temperatureChanged(Rooms::Room room, double value);
    void humidityChanged(Rooms::Room room, double value);
    void heatChanged(Rooms::Room room, double value);
    void dewChanged(Rooms::Room room, double value);
    void relayChanged(int card, int relay, bool relayState);
    void addHeating(const QString &name, const QString &id);
    void heatingStateChanged(const QString &id);

private:
    QThread workerThread;
};

#endif // CLIENTCONTROLLER_H
