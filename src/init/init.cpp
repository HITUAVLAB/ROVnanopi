#include "main.h"
#include "repeater.h"
#include "init.h"

extern Repeater repeater;

int init(void){
	serialPortInit();
	startSendingPthread();
}

int serialPortInit(void){
    int ret = 0;
    ret = repeater.Open("/dev/ttyS1", 115200, 8, NO, 1);
	if(ret == 0){
		printf("open serial error!\n");
		return 0;
	}
	else{
		printf("opem serial success!\n");
		return 1;
	}
}
