#include "canworker.h"
#include <QTimer>
#include <QEventLoop>
#include <QThread>
#include <QDebug>
#include <sstream>
#include <iostream>
#include "../../candy/src/candy.h"

CanWorker::CanWorker(QObject *parent) :
    QObject(parent) {
    this->_working =false;
    this->_abort = false;
    this->_candy = new Candy();
}

void CanWorker::shutdown() {
    if(this->_candy->isConnected()){
        this->_candy->shutdown();
    };
};

void CanWorker::requestWork() {
    this->_mutex.lock();
    this->_working = true;
    this->_abort = false;
    qDebug()<<"Request worker start in Thread "<<thread()->currentThreadId();
    this->_mutex.unlock();
    emit workRequested();
}

int CanWorker::joinCanNetwork() {
    this->_candy->setup();
    if(this->_candy->isConnected()){
        return 0;
    };
    return 1;
};

void CanWorker::abort() {
    this->_mutex.lock();
    if (_working) {
        this->_abort = true;
        qDebug()<<"Request worker aborting in Thread "<<thread()->currentThreadId();
    }
    this->_mutex.unlock();
}

std::vector<canfd_frame> CanWorker::getBuffer(){
    std::vector<canfd_frame> buffer;
    this->_mutex.lock();
    buffer = this->_frameBuffer;
    this->_mutex.unlock();
    return buffer;
};

void CanWorker::testing(){
    qDebug()<<"Testing!";
}

void CanWorker::doWork() {
    qDebug()<<"Starting worker process in Thread "<<thread()->currentThreadId();
    while(1) {
        this->_mutex.lock();
        bool abort = this->_abort;
        this->_mutex.unlock();
        if(abort) {
            break;
        };

        canfd_frame frame = this->_candy->recieve();
        std::stringstream userReadable;

        //std::cout << std::hex << frame.can_id << " : " << std::dec << frame.can_dlc << " ";
        userReadable << std::hex << frame.can_id;
        userReadable << " [ ";
        int i = 0;
        for(i = 0; i < 8; i++){
            int dataI  = frame.data[i];
            userReadable << std::hex << dataI << " ";
        };
        userReadable << "]";
        this->_frameBuffer.push_back(frame);
        int bufferSize = this->_frameBuffer.size() * sizeof(frame);
    };

    this->_mutex.lock();
    _working = false;
    this->_mutex.unlock();

    qDebug()<<"Worker process finished in Thread "<<thread()->currentThreadId();
    emit finished();
}
