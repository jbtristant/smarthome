#include <QDebug>
#include <QThread>
#include "clientworker.h"

ClientWorker::ClientWorker(QObject *parent) : QObject(parent)
{
    qRegisterMetaType<Rooms::Room>("Rooms::Room");
    qRegisterMetaType<HeatingState>("HeatingState");
}

ClientWorker::~ClientWorker()
{
    close();
    delete m_socket;
}

void ClientWorker::init()
{
    m_socket = new QTcpSocket;

    connect(m_socket, &QTcpSocket::readyRead, this, &ClientWorker::readyRead, Qt::DirectConnection);
    connect(m_socket, &QTcpSocket::connected, this, &ClientWorker::serverConnected);
    //connect(m_socket, &QTcpSocket::disconnected, this, &ClientWorker::disconnected);

    m_socket->connectToHost("localhost", 4817);
    if (!m_socket->waitForConnected()) {
        qWarning() << "Connection to server failed with error:" << m_socket->errorString();
    }

    emit heatingStateListAppend(HeatingState("Normal", "red"));
    emit heatingStateListAppend(HeatingState("Vacances", "green"));
    emit heatingStateListAppend(HeatingState("Fête", "blue"));
    emit heatingStateListAppend(HeatingState("Absent", "yellow"));
}

void ClientWorker::close()
{
    m_socket->write("exit\r\n");
    m_socket->disconnectFromHost();
    if (m_socket->state() != QAbstractSocket::UnconnectedState) m_socket->waitForDisconnected();
    //emit disconnected();
}

void ClientWorker::setRelay(int card, int relay, bool state)
{
    if (m_socket->state() == QAbstractSocket::ConnectedState)
        m_socket->write(QString("setRelay(%1,%2,%3)\r\n").arg(card).arg(relay).arg(state).toUtf8());
}

void ClientWorker::serverConnected()
{
    qInfo() << "Connected to server";
    m_socket->write("version 1.0\r\n");
}

void ClientWorker::readyRead()
{
    QByteArray bytes;
    char ba[65536];
    qint64 ret;
    while((ret = m_socket->readLine(ba, sizeof(ba))) != -1) {
        bytes.append(ba);
        if(!bytes.endsWith('\n')) {
            QThread::msleep(10);
            if (bytes.size() > 0) continue; else break;
        }
        //qDebug() << "recv data" << ((bytes.size() > 128)? bytes.mid(0, 128) + "...": bytes);

        parse(bytes);

        bytes.clear();
    }
    if(bytes.size() > 0) {
        qWarning() << "Message ignored: " << ((bytes.size() > 128)? bytes.mid(0, 128) + "...": bytes);
    }

}

void ClientWorker::parse(const QByteArray &data)
{
    QString line = QString(data);
    if (line.contains("ok version 1.0")) {
        m_socket->write("askHeatingStateList\r\n");
    }
    else if (line.startsWith("relayChanged(", Qt::CaseInsensitive)) {
        QStringList values = line.remove("relayChanged(").remove(")").split(",");
        if (values.size() != 3) return;
        emit relayChanged(values.at(0).toInt(), values.at(1).toInt(), values.at(2).toInt());
    }
    else if (line.startsWith("humidityChanged(", Qt::CaseInsensitive)) {
        QStringList values = line.remove("humidityChanged(").remove(")").split(",");
        if (values.size() != 2) return;
        emit humidityChanged((Rooms::Room)values.at(0).toInt(), values.at(1).toDouble());
    }
    else if (line.startsWith("temperatureChanged(", Qt::CaseInsensitive)) {
        QStringList values = line.remove("temperatureChanged(").remove(")").split(",");
        if (values.size() != 2) return;
        emit temperatureChanged((Rooms::Room)values.at(0).toInt(), values.at(1).toDouble());
    }
    else if (line.startsWith("heatChanged(", Qt::CaseInsensitive)) {
        QStringList values = line.remove("heatChanged(").remove(")").split(",");
        if (values.size() != 2) return;
        emit heatChanged((Rooms::Room)values.at(0).toInt(), values.at(1).toDouble());
    }
    else if (line.startsWith("dewChanged(", Qt::CaseInsensitive)) {
        QStringList values = line.remove("dewChanged(").remove(")").split(",");
        if (values.size() != 2) return;
        emit dewChanged((Rooms::Room)values.at(0).toInt(), values.at(1).toDouble());
    } else {
        qDebug() << "Client 1.0:" << ((data.size() > 128)? data.mid(0, 128) + "...": data);
    }

}
