#ifndef _PTHREAD_H_
#define _PTHREAD_H_

#define CREATE_SENDPTHREAD_SUCCESS 0
#define CREATE_TOGSPTHREAD_FAILED  1
#define CREATE_TOMBPTHREAD_FAILED  2

#include <pthread.h>

int networkInit(void);
int startSendingPthread(void);
void *sendToGS(void* ptr);
void *sendToMB(void* ptr);
void *videoStreamSend(void* ptr);
#endif
