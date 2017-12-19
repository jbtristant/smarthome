#ifndef HOMECONTROLLER_H
#define HOMECONTROLLER_H

#include <QObject>
#include <QThread>

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
    void temperatureChanged(double value);
    void humidityChanged(double value);
    void heatChanged(double value);
    void dewChanged(double value);
    void relayChanged(int card, int relay, bool relayState);

private:
    QThread workerThread;
};

#endif // HOMECONTROLLER_H
