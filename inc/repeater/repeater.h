#ifndef _REPEATER_H_
#define _REPEATER_H_

#include <iostream>
#include <pthread.h>
#include "serial.h"
#include "../inc/mavlink/common/mavlink.h"


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


#define MAX_BUF_SIZE 2048


class Repeater: public serial
{
private:
        char buf[MAX_BUF_SIZE];     //the buff which is used to transport the message
        mavlink_message_t msg;  //standard mavlink message
        mavlink_status_t status;
	int length;            // length of the msg
        //mavlink_heartbeat_t hb;

public:
	Repeater();
	~Repeater();
	char* getBuf();
	void setLength(int length_);
	int  getLength(void);
	mavlink_message_t* getMavlinkMsg(void);
	mavlink_status_t*  getMavlinkStatus(void);

	static void* sendToGS(void *ptr);
	static void* sendToMB(void *ptr);
	static void* sendVideo(void *ptr);
};



#endif
