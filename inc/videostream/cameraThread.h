#ifndef CAMERATHREAD_H_
#define CAMERATHREAD_H_

#include "PracticalSocket.h" // for UDPSocket and SocketException

#include "repeater.h"
#include "thread.h"

#include <iostream>
#include <cstdlib>

#include "opencv2/opencv.hpp"
#include "config.h"

#include "projectdebug.h"

using namespace std;
using namespace cv;

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
