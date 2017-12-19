#include <QDebug>

#include <QThread>

#include "homeworker.h"


void HomeWorker::init()
{
    arduinoMegaOne = new QSerialPort;
    arduinoMegaOne->setBaudRate(QSerialPort::Baud115200, QSerialPort::AllDirections);
    arduinoMegaOne->setPortName("/dev/tty.usbmodem411");

    connect(arduinoMegaOne, &QSerialPort::readyRead, this, &HomeWorker::arduinoMegaOneDataReceived);

    if (!arduinoMegaOne->open(QIODevice::ReadWrite)) {
        qInfo() << "Can not open arduino mega one serial port on port:" <<  arduinoMegaOne->portName() << "with error:" << arduinoMegaOne->errorString();
        return;
    }
    qDebug() << "Open arduino mega one serial port";

//    int nbrByteWrite = arduinoMegaOne->write("&relay 01 on$");
//    qDebug() << "number" << nbrByteWrite;
//    arduinoMegaOne->flush();
}

void HomeWorker::setRelay(int card, int relay, bool state)
{
    switch (card) {
    case 1:
        arduinoMegaOne->write(QString("&relay %1 %2$").arg(relay, 2, 10, QChar('0')).arg(state?"on":"off").toLocal8Bit());
        qDebug() << "write" << QString("&relay %1 %2$").arg(relay, 2, 10, QChar('0')).arg(state?"on":"off").toLocal8Bit();
        break;
    default:
        break;
    }
}

void HomeWorker::close()
{
    arduinoMegaOne->close();
}

void HomeWorker::arduinoMegaOneDataReceived()
{
    bufferMegaOne.append(arduinoMegaOne->readAll());
    processDataReceived(1);
}

void HomeWorker::processDataReceived(int card)
{
    QStringList splitEndLine = bufferMegaOne.split("\r\n");
    foreach (QString line, splitEndLine) {
        if (line.contains("Temperature: ")) {

            qDebug() << line << line.indexOf("Temperature: ") << line.mid(line.indexOf("Temperature: ") + 13, 5) << line.mid(line.indexOf("Temperature: ") + 13, 5).toDouble();
            emit temperatureChanged(line.mid(line.indexOf("Temperature: ") + 13, 5).toDouble());
        }
        if (line.contains("Humidity: ")) {

            emit humidityChanged(line.mid(line.indexOf("Humidity: ") + 10, 5).toDouble());
        }
        if (line.contains("Heat index: ")) {

            emit heatChanged(line.mid(line.indexOf("Heat index: ") + 12, 5).toDouble());
        }
        if (line.contains("Dew point: ")) {

            emit dewChanged(line.mid(line.indexOf("Dew point: ") + 11, 5).toDouble());
        }

        if (line.contains("&relay id") && line.contains("$")) {
            QStringList relay = line.remove("$").split(" ");
            if (relay.size() == 4) {
                qDebug() << line;
                emit relayChanged(card, relay.at(2).toInt(), relay.at(3) == "on"? true: false);
            }
        }

        // On place la dernière ligne dans le buffer
        if (line == splitEndLine.last()) bufferMegaOne = line;
    }

}
