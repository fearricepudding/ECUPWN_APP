#include "ConnectionManager.h"
#include "../../include/json.hpp"
#include "CanQueue.h"
#include "../udp_listener.h"

#include <iostream>
#include <QObject>
#include <boost/thread.hpp>

ConnectionManager::ConnectionManager(CanQueue* canQueue)
    : QObject(0) {
        this->canQueue = canQueue;
        this->refreshRate = 1;
        this->kill = false;
        boost::thread dataPushThread(&ConnectionManager::dataPusher, this, this->refreshRate);  
};

void ConnectionManager::openNewConnection(nlohmann::json connection) {
    this->kill = false;
    try{
        std::string ip = connection["ip"];
        std::string port = connection["port"];
        std::cout << "Open connection " << ip << ":" << port <<  std::endl;
        boost::thread newConnectionThread(&ConnectionManager::remoteConnection, this, this->canQueue, connection, this->kill);
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

void ConnectionManager::remoteConnection(CanQueue*queue, nlohmann::json connection, bool shouldExit) {
    std::cout << "Creating remtve connection" << std::endl;
    std::string ip = connection["ip"];
    std::string port = connection["port"];
    udp_listener *listener = new udp_listener(ip, port);
    emit(connStatusChanged(1));
    int status = listener->setup();
    if (status != 0) {
        emit(connStatusChanged(3));
        return;
    };
    emit(connStatusChanged(2));
    while(true) {
        if (shouldExit) {
            std::cout << "kill signal" << std::endl;
            break;
        };
        canfd_frame newFrame = listener->recieve();
        if (newFrame.len == 0) {
            std::cout << "Empty packet" << std::endl;
            continue;
        };
        std::cout << "[*] New frame: sending to queue" << std::endl;
        queue->add(newFrame);
    };
    return;
};

void ConnectionManager::dataPusher(int rate) {
    int timeout = 1000/rate;
    while(true) {
        emit(newData());
        boost::this_thread::sleep_for(boost::chrono::milliseconds(timeout)); 
    };
};

void ConnectionManager::disconnect() {
    std::cout << "setting all threads to close" << std::endl;    
    this->kill = true;
}
