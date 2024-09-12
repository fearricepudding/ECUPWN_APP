#pragma once

#include <boost/thread.hpp>

class ConnectionManager {
public:
    void addThread(boost::thread);
    void joinAll();
private:
    boost::thread_group connectionThreads;
};