#include "homeworker.h"
#include "homecontroller.h"

HomeController::HomeController(QObject *parent) : QObject(parent)
{
    HomeWorker *worker = new HomeWorker;

    worker->moveToThread(&workerThread);
    connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);
    connect(&workerThread, &QThread::started, worker, &HomeWorker::init);

    // Comunication between controller and worker
    connect(this, &HomeController::close, worker, &HomeWorker::close);
    connect(this, &HomeController::setRelay, worker, &HomeWorker::setRelay);

    connect(worker, &HomeWorker::temperatureChanged, this, &HomeController::temperatureChanged);
    connect(worker, &HomeWorker::humidityChanged, this, &HomeController::humidityChanged);
    connect(worker, &HomeWorker::heatChanged, this, &HomeController::heatChanged);
    connect(worker, &HomeWorker::dewChanged, this, &HomeController::dewChanged);
    connect(worker, &HomeWorker::relayChanged, this, &HomeController::relayChanged);

    workerThread.start();
}

HomeController::~HomeController()
{
    workerThread.quit();
    workerThread.wait();
}
