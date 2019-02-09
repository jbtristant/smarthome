#include <QDataStream>
#include <QStringList>
#include <QTcpSocket>

#include "client.h"

Client::Client(int socketDescriptor, QObject *parent)
    : QObject(parent)
{
    ClientWorker *worker = new ClientWorker(socketDescriptor);
    worker->moveToThread(&m_workerThread);
    connect(&m_workerThread, &QThread::finished, worker, &QObject::deleteLater);
    connect(&m_workerThread, &QThread::started, worker, &ClientWorker::init);

    // INPUT
    connect(this, &Client::write, worker, &ClientWorker::write);
    connect(this, &Client::handleSigHup, worker, &ClientWorker::handleSigHup);
    connect(this, &Client::temperatureChanged, worker, &ClientWorker::temperatureChanged);
    connect(this, &Client::humidityChanged, worker, &ClientWorker::humidityChanged);
    connect(this, &Client::heatChanged, worker, &ClientWorker::heatChanged);
    connect(this, &Client::dewChanged, worker, &ClientWorker::dewChanged);
    connect(this, &Client::relayChanged, worker, &ClientWorker::relayChanged);
    connect(this, &Client::sendHeatingStateList, worker, &ClientWorker::sendHeatingStateList);
    connect(this, &Client::heatingStateChanged, worker, &ClientWorker::heatingStateChanged);

    // OUTPUT
    connect(worker, &ClientWorker::disconnected, this, &Client::disconnected);
    connect(worker, &ClientWorker::error, this, &Client::error);
    connect(worker, &ClientWorker::setRelay, this, &Client::setRelay);
    connect(worker, &ClientWorker::askHeatingStateList, this, &Client::askHeatingStateList);
    connect(worker, &ClientWorker::setHeatingState, this, &Client::setHeatingState);

    m_workerThread.start();
}

Client::~Client()
{
    m_workerThread.quit();
    m_workerThread.wait();
}

ClientWorker::ClientWorker(int socketDescriptor, QObject *parent)
    : QObject(parent), m_socketDescriptor(socketDescriptor), m_majorVersion(-1), m_minorVersion(-1)
{
    qRegisterMetaType<Rooms::Room>("Rooms::Room");
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
    connect(m_socket, &QTcpSocket::disconnected, this, &ClientWorker::disconnected);

    if (!m_socket->setSocketDescriptor(m_socketDescriptor)) {
        emit error(m_socket->error());
        return;
    }
}

void ClientWorker::write(QByteArray data)
{
    m_socket->write(data);
    m_socket->flush();
}

void ClientWorker::handleSigHup()
{
    m_socket->write("I'm alive\r\n");
    m_socket->flush();
}

void ClientWorker::temperatureChanged(Rooms::Room room, double value)
{
    if (m_majorVersion == 1 && m_minorVersion == 0) {
        m_socket->write(QString("temperatureChanged(%1,%2)\r\n").arg(room).arg(value).toUtf8());
        m_socket->flush();
    }
}

void ClientWorker::humidityChanged(Rooms::Room room, double value)
{
    if (m_majorVersion == 1 && m_minorVersion == 0) {
        m_socket->write(QString("humidityChanged(%1,%2)\r\n").arg(room).arg(value).toUtf8());
        m_socket->flush();
    }
}

void ClientWorker::heatChanged(Rooms::Room room, double value)
{
    if (m_majorVersion == 1 && m_minorVersion == 0) {
        m_socket->write(QString("heatChanged(%1,%2)\r\n").arg(room).arg(value).toUtf8());
        m_socket->flush();
    }
}

void ClientWorker::dewChanged(Rooms::Room room, double value)
{
    if (m_majorVersion == 1 && m_minorVersion == 0) {
        m_socket->write(QString("dewChanged(%1,%2)\r\n").arg(room).arg(value).toUtf8());
        m_socket->flush();
    }
}

void ClientWorker::relayChanged(int card, int relay, bool relayState)
{
    if (m_majorVersion == 1 && m_minorVersion == 0) {
        m_socket->write(QString("relayChanged(%1,%2,%3)\r\n").arg(card).arg(relay).arg(relayState).toUtf8());
        m_socket->flush();
    }
}

void ClientWorker::sendHeatingStateList(const QString &serializedList)
{
    if (m_majorVersion == 1 && m_minorVersion == 0) {
        m_socket->write(QString("heatingStateList(%1)\r\n").arg(serializedList).toUtf8());
        m_socket->flush();
    }
}

void ClientWorker::heatingStateChanged(const QString &id)
{
    if (m_majorVersion == 1 && m_minorVersion == 0) {
        m_socket->write(QString("heatingStateChanged(%1)\r\n").arg(id).toUtf8());
        m_socket->flush();
    }
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

        if (m_majorVersion == -1) {
            if (bytes == "version 1.0\r\n") {
                m_majorVersion = 1;
                m_minorVersion = 0;
                m_socket->write("ok version 1.0\r\n");
                qInfo() << "client 1.0";
            } else {
                m_socket->write("bad\r\n");
                close();
            }
        } else {
            switch (m_majorVersion) {
            case 1:
                switch (m_minorVersion) {
                case 0:
                    parse_1_0(bytes);
                    break;
                default:
                    break;
                }
                break;
            default:
                break;
            }
        }

        if (bytes == "exit\r\n") {
            m_socket->write("ok exit\r\n");
            close();
        }

        bytes.clear();
    }
    if(bytes.size() > 0) {
        qWarning() << "Message ignored: " << ((bytes.size() > 128)? bytes.mid(0, 128) + "...": bytes);
    }

}

void ClientWorker::close()
{
    m_socket->write("sayonara\r\n");
    m_socket->disconnectFromHost();
    if (m_socket->state() != QAbstractSocket::UnconnectedState) m_socket->waitForDisconnected();
    emit disconnected();
}

void ClientWorker::parse_1_0(const QByteArray &data)
{
    qDebug() << "Client 1.0:" << ((data.size() > 128)? data.mid(0, 128) + "...": data);
    QString line = QString(data);
    if (line.startsWith("setRelay(", Qt::CaseInsensitive)) {
        QStringList values = line.remove("setRelay(").remove(")").split(",");
        if (values.size() != 3) return;
        emit setRelay(values.at(0).toInt(), values.at(1).toInt(), values.at(2).toInt());
        m_socket->write(QString("ok setRelay(%1,%2,%3) received\r\n").arg(values.at(0).toInt()).arg(values.at(1).toInt()).arg(values.at(2).toInt()).toUtf8());
    } else if (line.startsWith("askHeatingStateList", Qt::CaseInsensitive)) {
        emit askHeatingStateList();
        m_socket->write("ok askHeatingStateList() received\r\n");
    } else if (line.startsWith("setHeatingState(", Qt::CaseInsensitive)) {
        QString value = line.remove("setHeatingState(").remove(")\r\n");
        emit setHeatingState(value);
        m_socket->write(QString("ok setHeatingState(%1) received\r\n").arg(value).toUtf8());
    } else {
        m_socket->write("bad command unknown or arguments invalid\r\n");
    }
}
