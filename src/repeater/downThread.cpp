#include "downThread.h"

DownThread::DownThread(void){

}

DownThread::~DownThread(void){
    std::cout << "Destructing the uploading object and free the memory" << std::endl;
}

void DownThread::startSystem(){
    keepRunning = true;
    start();
}

void DownThread::stopSystem(){
    keepRunning = false;
    stop();
}

void DownThread::run(){
    std::cout << "Starting the downloading thread" << std::endl;

    while (keepRunning) {
        sleep(1000);
        std::cout << "Running the downloading thread" << std::endl;
    }

    std::cout << "Exiting downloading thread" << std::endl;
}
