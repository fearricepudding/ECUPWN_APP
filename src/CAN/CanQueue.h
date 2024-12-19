#pragma once
#include <linux/can.h>
#include <queue>
#include <mutex>
#include <list>

class CanQueue {
public:
    void add(canfd_frame);
    canfd_frame next();
    bool hasNext();
    std::list<canfd_frame> getQueue();
    int getBufferSize();
private:
    std::list<canfd_frame> _queue;
    std::mutex _lock;
};
