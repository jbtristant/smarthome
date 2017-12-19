#include <QTimer>

#include "waitsignalhelper.h"

WaitSignalHelper::WaitSignalHelper(QObject &obj, const char *sig)
    : timedout(false)
{
    connect(&obj, sig, &eventloop, SLOT(quit()));
}

WaitSignalHelper::WaitSignalHelper(QObject *obj, const char *sig)
    : timedout(false)
{
    if(obj) {
        connect(obj, sig, &eventloop, SLOT(quit()));
    }
}

bool WaitSignalHelper::wait(int timeout)
{

    if(timeout > 0) {
        QTimer::singleShot(timeout, this, &WaitSignalHelper::timeout);
    }

    timedout = false;

    eventloop.exec();

    return !timedout;
}

void WaitSignalHelper::timeout()
{
    timedout = true;
    eventloop.quit();
}
