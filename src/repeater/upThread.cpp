#include "upThread.h"
#include "cameraThread.h"
UpThread::UpThread(void){

}

UpThread::~UpThread(void){
    std::cout << "Destructing the uploading thread objrect and free the memory" << std::endl;
}

void UpThread::startSystem(){
    keepRunning = true;
    start();
}

void UpThread::stopSystem(){
    keepRunning = false;
    stop();
}

void UpThread::run(){
    std::cout << "Starting the uploading thread" << std::endl;

    CameraThread c;
    c.startSystem();

    while (keepRunning) {
        sleep(1000);
        std::cout << "Running the uploading thread" << std::endl;
    }

    c.stopSystem();
    std::cout << "Exiting uploading thread" << std::endl;
}
