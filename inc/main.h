#ifndef _MAIN_H_
#define _MAIN_H_

//some standard library
#include <stdio.h>

#include "repeater.h"     //the repeater class
#include "serial.h"       //the serial port operation class
#include "init.h"         //init function for the nanopi
#include "threadControl.h"      //pthread operation
#include "help.h"
extern Repeater repeater;


#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <time.h>
#include <csignal>
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

/*local include files*/
#include "upThread.h"
#include "downThread.h"

#endif
