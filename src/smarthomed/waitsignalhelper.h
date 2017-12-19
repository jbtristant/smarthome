#ifndef WAITSIGNALHELPER_H
#define WAITSIGNALHELPER_H

#include <QEventLoop>

class WaitSignalHelper : public QObject
{
    Q_OBJECT
public:
    WaitSignalHelper(QObject &obj, const char *sig);
    WaitSignalHelper(QObject *obj, const char *sig);

    bool wait(int timeout);

public slots:
    void timeout();

private:
    bool timedout;
    QEventLoop eventloop;
};

#endif // WAITSIGNALHELPER_H
