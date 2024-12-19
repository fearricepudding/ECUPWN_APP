#pragma once

#include <QObject>
#include <QMutex>
#include "../../candy/src/candy.h"
#include <linux/can.h>
#include <linux/can/raw.h>

class CanWorker : public QObject
{
    Q_OBJECT

public:
    explicit CanWorker(QObject *parent = 0);
    void requestWork();
    void abort();
    int joinCanNetwork();
    void shutdown();
    std::vector<canfd_frame> getBuffer();

private:
    bool _abort;
    bool _working;
    QMutex _mutex;
    Candy *_candy;
    std::vector<canfd_frame> _frameBuffer;

signals:
    void workRequested();
    void valueChanged(const QString &value);
    void finished();

public slots:
    void doWork();
    void testing();
};

