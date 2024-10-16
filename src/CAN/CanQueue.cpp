#include "CanQueue.h"

#include <linux/can.h>
#include <mutex>
#include <queue>
#include <list>

bool CanQueue::hasNext() {
    this->_lock.lock();
    if (this->_queue.size() <= 0) {
        this->_lock.unlock();
        return false;
    };
    this->_lock.unlock();
    return true;
};

can_frame CanQueue::next() {
    this->_lock.lock();
    can_frame frame = (can_frame) this->_queue.front();
    this->_queue.pop_front();
    this->_lock.unlock();
    return frame;
};

void CanQueue::add(can_frame frame) {
    this->_lock.lock();
    this->_queue.push_back(frame);
    this->_lock.unlock();
};

std::list<can_frame> CanQueue::getQueue() {
    return this->_queue;
};