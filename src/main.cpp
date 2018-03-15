#include <stdio.h>
#include "../inc/main.h"
#include "mavlink/common/mavlink.h"    //mavlink头文件

#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <time.h>
#if (defined __QNX__) | (defined __QNXNTO__)
/* QNX specific headers */
#include <unix.h>
#else
/* Linux / MacOS POSIX timer headers */
#include <sys/time.h>
#include <time.h>
#include <arpa/inet.h>
#include <stdbool.h> /* required for the definition of bool in C99 */
#endif

/*线程相关头文件*/
#include <pthread.h>

uint64_t microsSinceEpoch();

Repeater repeater;

int main(int argc, char** argv)
{
	/*print help information*/
	help(argc,argv);

	/*excute initiation work*/
	/*open the serial port
	 *create the pthread */
	init();

	while(1)
	{
		sleep(500);
	}
	//pthread_join(MBtoGS_thread,NULL);	
	//pthread_join(GStoMB_thread,NULL);
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

