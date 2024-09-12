#pragma once
#include <linux/can.h>
#include <queue>
#include <mutex>

class CanQueue {
public:
    void add(can_frame);
    can_frame next();
    bool hasNext();
private:
    std::queue<can_frame> _queue;
    std::mutex _lock;
};