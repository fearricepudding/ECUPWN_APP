#include "CanQueue.h"

#include <linux/can.h>
#include <mutex>
#include <queue>

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
    this->_queue.pop();
    this->_lock.unlock();
    return frame;
};

void CanQueue::add(can_frame frame) {
    this->_lock.lock();
    this->_queue.push(frame);
    this->_lock.unlock();
};