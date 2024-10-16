#pragma once
#include <linux/can.h>
#include <queue>
#include <mutex>
#include <list>

class CanQueue {
public:
    void add(can_frame);
    can_frame next();
    bool hasNext();
    std::list<can_frame> getQueue();
private:
    std::list<can_frame> _queue;
    std::mutex _lock;
};