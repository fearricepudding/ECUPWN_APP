#include "canworker.h"
#include <QTimer>
#include <QEventLoop>
#include <QThread>
#include <QDebug>
#include <sstream>
#include <iostream>
#include "../candy/src/candy.h"

CanWorker::CanWorker(QObject *parent) :
    QObject(parent)
{
    _working =false;
    _abort = false;
    _candy = new Candy();
}

void CanWorker::requestWork()
{
    mutex.lock();
    _working = true;
    _abort = false;
    qDebug()<<"Request worker start in Thread "<<thread()->currentThreadId();
    mutex.unlock();

    emit workRequested();
}

int CanWorker::joinCanNetwork(){
    _candy->setup();
}

void CanWorker::abort()
{
    mutex.lock();
    if (_working) {
        _abort = true;
        qDebug()<<"Request worker aborting in Thread "<<thread()->currentThreadId();
    }
    mutex.unlock();
}


void CanWorker::doWork()
{
    qDebug()<<"Starting worker process in Thread "<<thread()->currentThreadId();

    while(1){
       // Checks if the process should be aborted
        mutex.lock();
        bool abort = _abort;
        mutex.unlock();
        if(abort){
            break;
        }

        can_frame frame = _candy->recieve();
        std::stringstream userReadable;

        printf("can_id = 0x%X\r\ncan_dlc = %d \r\n", frame.can_id, frame.can_dlc);
        userReadable << std::hex << frame.can_id;
        userReadable << " [ ";
        int i = 0;
        for(i = 0; i < 8; i++){
            //printf("data[%d] = %d\r\n", i, frame.data[i]);
            int dataI  = frame.data[i];
            std::cout << "data[" << i << "] = [" << std::hex << dataI << "]" << std::endl;
            userReadable << std::hex << dataI << " ";
        };

        userReadable << "]";

        std::cout << userReadable.str() << std::endl;
	

        // Once we're done waiting, value is updated
        emit valueChanged(QString::fromUtf8(userReadable.str().c_str()));
    }

    // Set _working to false, meaning the process can't be aborted anymore.
    mutex.lock();
    _working = false;
    mutex.unlock();

    qDebug()<<"Worker process finished in Thread "<<thread()->currentThreadId();

    //Once 60 sec passed, the finished signal is sent
    emit finished();
}
