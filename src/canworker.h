#pragma once

#include <QObject>
#include <QMutex>
#include "../candy/src/candy.h"
#include <linux/can.h>
#include <linux/can/raw.h>

struct can_frame;

class CanWorker : public QObject
{
    Q_OBJECT

public:
    explicit CanWorker(QObject *parent = 0);
    void requestWork();
    void abort();
    int joinCanNetwork();
    void shutdown();
    std::vector<can_frame> getBuffer();

private:
    bool _abort;
    bool _working;
    QMutex _mutex;
    Candy *_candy;
    std::vector<can_frame> _frameBuffer;

signals:
    void workRequested();
    void valueChanged(const QString &value);
    void finished();

public slots:
    void doWork();
};

