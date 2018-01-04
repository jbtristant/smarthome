#ifndef HOMEWORKER_H
#define HOMEWORKER_H

#include <QObject>
#include <QSerialPort>

#include "common.h"

class HomeWorker : public QObject
{
    Q_OBJECT
public:
    explicit HomeWorker(QObject *parent = 0);

signals:
    void temperatureChanged(Rooms::Room room, double value);
    void humidityChanged(Rooms::Room room, double value);
    void heatChanged(Rooms::Room room, double value);
    void dewChanged(Rooms::Room room, double value);
    void relayChanged(int card, int relay, bool relayState);

public slots:
    void init();
    void close();

    void setRelay(int card, int relay, bool state);

private slots:
    void arduinoMegaOneDataReceived();

private:
    QSerialPort *arduinoMegaOne;
    QString bufferMegaOne;

    void processDataReceived(int card);
};

#endif // HOMEWORKER_H
