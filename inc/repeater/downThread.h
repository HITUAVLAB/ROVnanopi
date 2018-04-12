#ifndef DOWNTHREAD_H_
#define DOWNTHREAD_H_

#include"thread.h"
#include"main.h"
#include"repeater.h"
#include<iostream>

class DownThread : public Thread{
private:
    //The associated thread's for run function
    void run();

    //Is running?
    bool keepRunning;

public:
    DownThread(void);
    ~DownThread(void);

    //start/stop the system and respective thread
    void startSystem();
    void stopSystem();

};

#endif
