#ifndef HOMEWORKER_H
#define HOMEWORKER_H

#include <QObject>
#include <QSerialPort>

class HomeWorker : public QObject
{
    Q_OBJECT
public:
    explicit HomeWorker(QObject *parent = 0) : QObject(parent) {}

signals:
    void temperatureChanged(double value);
    void humidityChanged(double value);
    void heatChanged(double value);
    void dewChanged(double value);
    void relayChanged(int relay, bool relayState);

public slots:
    void init();

    void setRelay(int card, int relay, bool state);

private slots:
    void dataReceived();

private:
    QSerialPort *arduinoMegaOne;
    QString bufferMegaOne;

    void processDataReceived();
};

#endif // HOMEWORKER_H
