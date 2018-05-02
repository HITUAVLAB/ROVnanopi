#include "downThread.h"
#include "mavlink.h"

extern Repeater repeater;

DownThread::DownThread(void){

}

DownThread::~DownThread(void){
#ifdef DOWNTHREADDEBUG
    std::cout << "Destructing the uploading object and free the memory" << std::endl;
#endif
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
    ssize_t recvLength; 
#ifdef DOWNTHREADDEBUG
    std::cout << "Starting the downloading thread" << std::endl;
#endif

    while (keepRunning) {
        //sleep(1000);
        //std::cout << "Running the downloading thread" << std::endl;
        pthread_mutex_lock(&mut);
        recvLength = repeater.receiveBuf();
        if(recvLength > 0){
#ifdef DOWNTHREADDEBUG
            printf("received buf from ground station\n");
#endif
            //send received message to main board through serial port
            mavlink_message_t msg;
            mavlink_status_t status;
#ifdef DOWNTHREADDEBUG
            std::cout << "received buf is: " << recvLength << std::endl;
#endif
            for(int i = 0;i < recvLength; i++){
                if(mavlink_parse_char(MAVLINK_COMM_0,repeater.getBuf()[i],repeater.getMavlinkMsg(),repeater.getMavlinkStatus())){
#ifdef DOWNTHREADDEBUG
                    printf("\nReceived packet: SYS: %d, COMP: %d, LEN: %d, MSG ID: %d\n", repeater.getMavlinkMsg()->sysid, repeater.getMavlinkMsg()->compid, \
                                                                                          repeater.getMavlinkMsg()->len,   repeater.getMavlinkMsg()->msgid);
                    
#endif
                    //send mavlink message to mainboard
                    if(repeater.Write(repeater.getBuf(),recvLength)){
#ifdef DOWNTHREADDEBUG
                        printf("buf write success!\n");
#endif                        

                    }
                   
                }

            }
        }
        pthread_mutex_unlock(&mut);        
    }

    std::cout << "Exiting downloading thread" << std::endl;
}
