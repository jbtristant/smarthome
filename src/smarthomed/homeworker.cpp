#include <QCoreApplication>
#include <QDebug>
#include <QSettings>
#include <QThread>

#include "homeworker.h"


HomeWorker::HomeWorker(QObject *parent) : QObject(parent)
{
    qRegisterMetaType<Rooms::Room>("Rooms::Room");
}

void HomeWorker::init()
{
    QSettings settings(QSettings::SystemScope, qApp->organizationName(), qApp->applicationName(), this);
    if (!settings.contains("arduino mega one serial port name")) settings.setValue("arduino mega one serial port name", "/dev/tty.usbmodem411");
    QString arduinoMegaOneSerialPortName = settings.value("arduino mega one serial port name", "/dev/tty.usbmodem411").toString();

    arduinoMegaOne = new QSerialPort;
    arduinoMegaOne->setBaudRate(QSerialPort::Baud115200, QSerialPort::AllDirections);
    arduinoMegaOne->setPortName(arduinoMegaOneSerialPortName);

    connect(arduinoMegaOne, &QSerialPort::readyRead, this, &HomeWorker::arduinoMegaOneDataReceived);

    if (!arduinoMegaOne->open(QIODevice::ReadWrite)) {
        qWarning() << "Can not open arduino mega one serial port on port:" <<  arduinoMegaOne->portName() << "with error:" << arduinoMegaOne->errorString();
        return;
    }
    qInfo() << "Open arduino mega one serial port";
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
        if (line.contains("Salon Temperature: ")) {
            //qDebug() << line << line.indexOf("Temperature: ") << line.mid(line.indexOf("Temperature: ") + 13, 5) << line.mid(line.indexOf("Temperature: ") + 13, 5).toDouble();
            emit temperatureChanged(Rooms::Room::Salon, line.mid(line.indexOf("Salon Temperature: ") + 19, 5).toDouble());
        }
        if (line.contains("Salon Humidity: ")) {

            emit humidityChanged(Rooms::Room::Salon, line.mid(line.indexOf("Salon Humidity: ") + 16, 5).toDouble());
        }
        if (line.contains("Salon Heat index: ")) {

            emit heatChanged(Rooms::Room::Salon, line.mid(line.indexOf("Salon Heat index: ") + 18, 5).toDouble());
        }
        if (line.contains("Salon Dew point: ")) {

            emit dewChanged(Rooms::Room::Salon, line.mid(line.indexOf("Salon Dew point: ") + 17, 5).toDouble());
        }
        if (line.contains("SDB Temperature: ")) {
            emit temperatureChanged(Rooms::Room::SalleDeBain, line.mid(line.indexOf("SDB Temperature: ") + 17, 5).toDouble());
        }
        if (line.contains("SDB Humidity: ")) {

            emit humidityChanged(Rooms::Room::SalleDeBain, line.mid(line.indexOf("SDB Humidity: ") + 14, 5).toDouble());
        }
        if (line.contains("SDB Heat index: ")) {

            emit heatChanged(Rooms::Room::SalleDeBain, line.mid(line.indexOf("SDB Heat index: ") + 16, 5).toDouble());
        }
        if (line.contains("SDB Dew point: ")) {

            emit dewChanged(Rooms::Room::SalleDeBain, line.mid(line.indexOf("SDB Dew point: ") + 15, 5).toDouble());
        }
        if (line.contains("Hall Temperature: ")) {
            emit temperatureChanged(Rooms::Room::Hall, line.mid(line.indexOf("Hall Temperature: ") + 18, 5).toDouble());
        }
        if (line.contains("Hall Humidity: ")) {

            emit humidityChanged(Rooms::Room::Hall, line.mid(line.indexOf("Hall Humidity: ") + 15, 5).toDouble());
        }
        if (line.contains("Hall Heat index: ")) {

            emit heatChanged(Rooms::Room::Hall, line.mid(line.indexOf("Hall Heat index: ") + 17, 5).toDouble());
        }
        if (line.contains("Hall Dew point: ")) {

            emit dewChanged(Rooms::Room::Hall, line.mid(line.indexOf("Hall Dew point: ") + 16, 5).toDouble());
        }
        if (line.contains("Chambre Temperature: ")) {
            emit temperatureChanged(Rooms::Room::Chambre, line.mid(line.indexOf("Chambre Temperature: ") + 21, 5).toDouble());
        }
        if (line.contains("Chambre Humidity: ")) {

            emit humidityChanged(Rooms::Room::Chambre, line.mid(line.indexOf("Chambre Humidity: ") + 18, 5).toDouble());
        }
        if (line.contains("Chambre Heat index: ")) {

            emit heatChanged(Rooms::Room::Chambre, line.mid(line.indexOf("Chambre Heat index: ") + 20, 5).toDouble());
        }
        if (line.contains("Chambre Dew point: ")) {

            emit dewChanged(Rooms::Room::Chambre, line.mid(line.indexOf("Chambre Dew point: ") + 19, 5).toDouble());
        }

        if (line.contains("&relay id") && line.contains("$")) {
            QStringList relay = line.remove("$").split(" ");
            if (relay.size() == 4) {
                qDebug() << line;
                emit relayChanged(card, relay.at(2).toInt(), relay.at(3) == "on"? true: false);
            }
        }

        // Add the last line into the buffer
        if (line == splitEndLine.last()) bufferMegaOne = line;
    }

}
