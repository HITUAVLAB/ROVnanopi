#ifndef UPTHREAD_H_
#define UPTHREAD_H_

#include"thread.h"
#include<iostream>

#include "main.h"

class UpThread : public Thread{
private:
    //The associated thread's for run function
    void run();

    //Is running?
    bool keepRunning;

public:
    UpThread(void);
    ~UpThread(void);

    //start/stop the system and respective thread
    void startSystem();
    void stopSystem();

};

#endif
