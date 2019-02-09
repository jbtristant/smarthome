#include "clientcontroller.h"
#include "clientworker.h"
#include "heatingstate.h"

ClientController::ClientController(QObject *parent) : QObject(parent)
{
    ClientWorker *worker = new ClientWorker;

    worker->moveToThread(&workerThread);
    connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);
    connect(&workerThread, &QThread::started, worker, &ClientWorker::init);

    connect(this, &ClientController::setRelay, worker, &ClientWorker::setRelay);
    connect(this, &ClientController::setHeatingState, worker, &ClientWorker::setHeatingState);

    connect(worker, &ClientWorker::temperatureChanged, this, &ClientController::temperatureChanged);
    connect(worker, &ClientWorker::humidityChanged, this, &ClientController::humidityChanged);
    connect(worker, &ClientWorker::heatChanged, this, &ClientController::heatChanged);
    connect(worker, &ClientWorker::dewChanged, this, &ClientController::dewChanged);
    connect(worker, &ClientWorker::relayChanged, this, &ClientController::relayChanged);
    connect(worker, &ClientWorker::addHeating, this, &ClientController::addHeating);
    connect(worker, &ClientWorker::heatingStateChanged, this, &ClientController::heatingStateChanged);


    workerThread.start();
}

ClientController::~ClientController()
{
    workerThread.quit();
    workerThread.wait();
}
