#include "ConnectionManager.h"
#include "../../include/json.hpp"
#include "CanQueue.h"

#include <iostream>
#include <QObject>
#include <boost/thread.hpp>

ConnectionManager::ConnectionManager(CanQueue* canQueue)
    : QObject(0) {
        this->canQueue = canQueue;
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
    //
    while(true) {
        std::cout << "Ping" << std::endl;
        can_frame frame;
        queue->add(frame);
        emit(newData());
        boost::this_thread::sleep_for(boost::chrono::milliseconds(200));
    }
}