/*A thread lib for multi thread*/
#include <time.h>
#include "thread.h"

#ifdef WIN32
#include <windows.h>
#endif

//Static variables
bool Thread::ourInitializedFlag = false;
pthread_key_t Thread::ourKey;
unsigned int Thread::ourCount;

/** The constructor performs global initialization of the Thread class if necessary. */
Thread::Thread() : myRunningFlag(false), myStopFlag(false){
    if(!ourInitializedFlag){
        init();
        ourInitializedFlag = true;
    }
}

Thread::~Thread(){
    if(isRunning()){
        stop();   //stop the thread, this doesn't really stop the thread, it only tell the system that you should stop the thread
        join();   //join the thread until all the other work is done
    }
}

/*Use pthread to create a new thread*/
void Thread::start(Runnable *runnable){
    myRunnable = runnable ? runnable : this;
    myStopFlag = false;
    pthread_attr_t attr;   //pthread attributes object
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    ourCount++;
    pthread_create(&myID,&attr,threadproc,this);
}

void Thread::stop(){
    myStopFlag = true;
}

bool Thread::shouldStop() const{
    return myStopFlag;
}

bool Thread::isRunning() const{
    return myRunningFlag;
}

void Thread::join(){
    pthread_join(myID,0);
}

pthread_t Thread::getID() const{
    return myID;
}

unsigned int Thread::count(){
    return ourCount;
}

Thread* Thread::getCurrent(){
    return (Thread*)pthread_getspecific(ourKey);
}

/* Uses nano sleep*/
void Thread::sleep(unsigned int milli){
#ifdef WIN32
    Sleep(milli);
#else
    struct timespec ts = {milli/1000,(milli%1000)*1000000 };
    nanosleep(&ts , 0);
#endif
}

bool Thread::init(){
    ourCount = 0;
    pthread_key_create(&ourKey,0);
    return true;
}

void* Thread::threadproc(void *param){
    Thread* thread = (Thread*)param;
    pthread_setspecific(ourKey,thread);
    thread->myRunningFlag = true;
    if(thread->myRunnable)
        thread->myRunnable->run();
    else
        thread->run();
    thread->myRunningFlag = false;
    ourCount--;
    return 0;

}
