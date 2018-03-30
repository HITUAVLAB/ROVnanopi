#include "cameraThread.h"

CameraThread::CameraThread(void){

}

CameraThread::~CameraThread(void){
    std::cout << "Destructing the uploading object and free the memory" << std::endl;
}

void CameraThread::startSystem(){
    keepRunning = true;
    start();
}

void CameraThread::stopSystem(){
    keepRunning = false;
    stop();
}

void CameraThread::run(){
    std::cout << "Starting the camera thread" << std::endl;

    while (keepRunning) {
        sleep(1000);
        std::cout << "Running the camera thread" << std::endl;
    }

    std::cout << "Exiting camera thread" << std::endl;

}
