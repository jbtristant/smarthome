#ifndef HOMECONTROLLER_H
#define HOMECONTROLLER_H

#include <QObject>
#include <QThread>

#include <common.h>

class HomeController : public QObject
{
    Q_OBJECT
public:
    explicit HomeController(QObject *parent = 0);
    ~HomeController();

signals:
    // INPUT
    void close();
    void setRelay(int card, int relay, bool state);

    // OUTPUT
    void temperatureChanged(Rooms::Room room, double value);
    void humidityChanged(Rooms::Room room, double value);
    void heatChanged(Rooms::Room room, double value);
    void dewChanged(Rooms::Room room, double value);
    void relayChanged(int card, int relay, bool relayState);

private:
    QThread workerThread;
};

#endif // HOMECONTROLLER_H
