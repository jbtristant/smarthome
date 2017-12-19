#include <QDebug>
#include <QThread>
#include "clientworker.h"

ClientWorker::ClientWorker(QObject *parent) : QObject(parent)
{

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
    if (line.startsWith("relayChanged(", Qt::CaseInsensitive)) {
        QStringList values = line.remove("relayChanged(").remove(")").split(",");
        if (values.size() != 3) return;
        emit relayChanged(values.at(0).toInt(), values.at(1).toInt(), values.at(2).toInt());
    }
    else if (line.startsWith("humidityChanged(", Qt::CaseInsensitive)) {
        QString value = line.remove("humidityChanged(").remove(")");
        emit humidityChanged(value.toDouble());
    }
    else if (line.startsWith("temperatureChanged(", Qt::CaseInsensitive)) {
        QString value = line.remove("temperatureChanged(").remove(")");
        emit temperatureChanged(value.toDouble());
    }
    else if (line.startsWith("heatChanged(", Qt::CaseInsensitive)) {
        QString value = line.remove("heatChanged(").remove(")");
        emit heatChanged(value.toDouble());
    }
    else if (line.startsWith("dewChanged(", Qt::CaseInsensitive)) {
        QString value = line.remove("dewChanged(").remove(")");
        emit dewChanged(value.toDouble());
    } else {
        qDebug() << "Client 1.0:" << ((data.size() > 128)? data.mid(0, 128) + "...": data);
    }

}
