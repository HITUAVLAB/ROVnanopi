#ifndef CAMERATHREAD_H_
#define CAMERATHREAD_H_

#include "thread.h"
#include <iostream>

class CameraThread : public Thread{
private:
    void run();

    //Is running?
    bool keepRunning;

public:
    CameraThread();
    ~CameraThread();

    //Start/stop the system and respective thread
    void startSystem();
    void stopSystem();

};

#endif
