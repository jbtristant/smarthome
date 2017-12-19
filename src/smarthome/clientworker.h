#ifndef CLIENTWORKER_H
#define CLIENTWORKER_H

#include <QObject>
#include <QTcpSocket>

class ClientWorker : public QObject
{
    Q_OBJECT
public:
    explicit ClientWorker(QObject *parent = nullptr);
    ~ClientWorker();

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

protected slots:
    void serverConnected();
    void readyRead();
    void parse(const QByteArray &data);


protected:
    QTcpSocket *m_socket;

};

#endif // CLIENTWORKER_H
