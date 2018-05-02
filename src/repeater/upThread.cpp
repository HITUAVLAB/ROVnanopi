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

#ifdef UPTHREADDEBUG
    std::cout << "Starting the uploading thread" << std::endl;
#endif
    int bytes_sent;

    CameraThread c;
    //c.startSystem();

    while (keepRunning) {
#ifdef UPTHREADDEBUG
        //sleep(1000);
        //std::cout << "Running the uploading thread" << std::endl;
#endif
        pthread_mutex_lock(&mut);
#ifdef UPTHREADDEBUG
        //printf("Start reading\n");
#endif
        repeater.setLength( repeater.Read(repeater.getBuf()) );     //length is the byte the uart read
        if(repeater.getLength()){                                   //buf is not empty
            for(int i = 0; i < repeater.getLength(); i++){
#ifdef UPTHREADDEBUG
            //std::cout << repeater.getLength() << " bytes received:" << std::endl;
            //printf("%.2X ",repeater.getBuf()[i]);
#endif            
            if (mavlink_parse_char(MAVLINK_COMM_0, repeater.getBuf()[i], repeater.getMavlinkMsg(), repeater.getMavlinkStatus() )){
                //bytes_sent = sendto(sock, repeater.getBuf(), repeater.getLength(), 0, (struct sockaddr*)&gcAddr, sizeof(struct sockaddr_in));
                repeater.sendBuf();
#ifdef UPTHREADDEBUG
                
                printf("mavlink message received\n");
                printf("the message ID is: %d\n",repeater.getMavlinkMsg()->msgid);
#endif
            }
        }
#ifdef UPTHREADDEBUG
            printf("%d\n",repeater.getLength());
#endif        
	}
        memset(repeater.getBuf(),0,MAX_BUF_SIZE);


        pthread_mutex_unlock(&mut);


    }

    //c.stopSystem();
#ifdef UPTHREADDEBUG
    std::cout << "Exiting uploading thread" << std::endl;
#endif
}
