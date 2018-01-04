#ifndef CLIENTCONTROLLER_H
#define CLIENTCONTROLLER_H

#include <QObject>
#include <QThread>

#include "common.h"
#include "heatingstate.h"

class ClientController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<QObject*> heatingStateList READ heatingStateList WRITE setHeatingStateList NOTIFY heatingStateListChanged)

public:
    explicit ClientController(QObject *parent = nullptr);
    ~ClientController();

    QList<QObject*> heatingStateList() const;

public slots:
    void setHeatingStateList(QList<QObject*> heatingStateList);

signals:
    // INPUT
    void close();
    void setRelay(int card, int relay, bool state);

    // OUTPUT
    void temperatureChanged(Rooms::Room room, double value);
    void humidityChanged(Rooms::Room room, double value);
    void heatChanged(Rooms::Room room, double value);
    void dewChanged(Rooms::Room room, double value);
    void relayChanged(int card, int relay, bool relayState);

    void heatingStateListChanged(QList<QObject*> heatingStateList);

private slots:
    void onHeatingStateListAppend(const HeatingState &heatingState);


private:
    QThread workerThread;
    QList<QObject*> m_heatingStateList;
};

//QList<QObject*> m_heatingStateList;
//m_heatingStateList.append(new HeatingState("Normal", "red"));
//m_heatingStateList.append(new HeatingState("Vacances", "green"));
//m_heatingStateList.append(new HeatingState("Fête", "blue"));
//m_heatingStateList.append(new HeatingState("Absent", "yellow"));


#endif // CLIENTCONTROLLER_H
