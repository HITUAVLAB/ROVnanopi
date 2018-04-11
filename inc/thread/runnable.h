#ifndef RUNNABLE_H_
#define RUNNABLE_H_

// this is an abstract base class for anything with a run() method
class Runnable{
public:
    virtual void run()=0; //pure virtual function
	virtual ~Runnable(){};  //calling the interface function

};

#endif
