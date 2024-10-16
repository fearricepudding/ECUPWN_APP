#pragma once

#include "../../include/json.hpp"
#include "CanQueue.h"

#include <linux/can.h>
#include <boost/thread.hpp>
#include <QObject>

class ConnectionManager : public QObject {
    Q_OBJECT

private slots:
    void openNewConnection(nlohmann::json);
signals:
    void newData();

public:
    ConnectionManager(CanQueue*);
    void addThread(boost::thread*);
    void joinAll();
    int refreshRate;
private:
    CanQueue* canQueue;
    void remoteConnection(CanQueue *, nlohmann::json);
    boost::thread_group connectionThreads;

};