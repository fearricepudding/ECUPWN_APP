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
    void disconnect();
signals:
    void newData();
    void connStatusChanged(int);

public:
    ConnectionManager(CanQueue*);
    void addThread(boost::thread*);
    void joinAll();
    int refreshRate;
    void closeAll();
private:
    CanQueue* canQueue;
    void remoteConnection(CanQueue *, nlohmann::json, bool);
    boost::thread_group connectionThreads;
    void dataPusher(int);
    bool kill;

};
