#include <stdio.h>
#include "main.h"
#include "mavlink.h"    //mavlink头文件

static volatile int keepRunning = 1;

uint64_t microsSinceEpoch();

Repeater repeater;
pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;

/*receive the ctrl + c interupt signal, stop the main thread*/
void sig_handler( int sig )
{
    if ( sig == SIGINT)
    {
        keepRunning = 0;
    }
}

int main(int argc, char** argv)
{
#ifdef DEBUG
    std::cout << "Starting the ROV groundstation, this is the debug release" << std::endl;
#endif
    signal( SIGINT, sig_handler );
    // Check if --help flag was used

    if(argc == 2){
        repeater.setUserDefinedIP(argv[1]);

    }

    UpThread u;
    DownThread d;
    //CameraThread c;

	/*print help information*/
	help(argc,argv);

	/*excute initiation work*/
	/*open the serial port*/
	/*initialize network*/
	init();

    u.startSystem();
    d.startSystem();
    //c.startSystem();

    while(keepRunning)
    {
        std::cout <<"running"<<std::endl;
        sleep(1000);
    }
    std::cout << "end the program" << std::endl;
    
    //c.stopSystem();
    u.stopSystem();
    d.stopSystem();
	//repeater.Close();
	
	return 0;
}


#if (defined __QNX__) | (defined __QNXNTO__)
uint64_t microsSinceEpoch()
{
	
	struct timespec time;
	
	uint64_t micros = 0;
	
	clock_gettime(CLOCK_REALTIME, &time);  
	micros = (uint64_t)time.tv_sec * 1000000 + time.tv_nsec/1000;
	
	return micros;
}
#else
uint64_t microsSinceEpoch()
{
	
	struct timeval tv;
	
	uint64_t micros = 0;
	
	gettimeofday(&tv, NULL);  
	micros =  ((uint64_t)tv.tv_sec) * 1000000 + tv.tv_usec;
	
	return micros;
}
#endif

