#include "ConnectionManager.h"
#include "../../include/json.hpp"
#include "CanQueue.h"

#include <iostream>
#include <QObject>
#include <boost/thread.hpp>

ConnectionManager::ConnectionManager(CanQueue* canQueue)
    : QObject(0) {
        this->canQueue = canQueue;
        this->refreshRate = 1;

        boost::thread dataPushThread(&ConnectionManager::dataPusher, this, this->refreshRate);
};

void ConnectionManager::openNewConnection(nlohmann::json connection) {
    try{
        std::string ip = connection["ip"];
        std::string port = connection["port"];
        std::cout << "Open connection " << ip << ":" << port <<  std::endl;
        boost::thread newConnectionThread(&ConnectionManager::remoteConnection, this, this->canQueue, connection);
    }catch(std::exception &e) {
        std::cout << e.what() << std::endl;
    };
}

void ConnectionManager::addThread(boost::thread *thread) {
    this->connectionThreads.add_thread(thread);
};

void ConnectionManager::joinAll() {
    this->connectionThreads.join_all();
};

void ConnectionManager::remoteConnection(CanQueue*queue, nlohmann::json connection) {
    std::cout << "Creating remove connection" << std::endl;
    while(true) {
        // Get the new data from connection for *refreshRate* time
        canfd_frame frame;
        queue->add(frame);
        boost::this_thread::sleep_for(boost::chrono::milliseconds(4)); 
    };
};

void ConnectionManager::dataPusher(int rate) {
    int timeout = 1000/rate;
    while(true) {
        emit(newData());
        boost::this_thread::sleep_for(boost::chrono::milliseconds(timeout)); 
    };
};
