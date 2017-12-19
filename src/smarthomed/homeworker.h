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
