#ifndef CLIENTCONTROLLER_H
#define CLIENTCONTROLLER_H

#include <QObject>
#include <QThread>

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

    // OUTPUT
    void temperatureChanged(double value);
    void humidityChanged(double value);
    void heatChanged(double value);
    void dewChanged(double value);
    void relayChanged(int card, int relay, bool relayState);

private:
    QThread workerThread;
};

#endif // CLIENTCONTROLLER_H
