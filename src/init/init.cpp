#include "main.h"
#include "repeater.h"
#include "init.h"

extern Repeater repeater;

int init(void){
	//serialPortInit();
	repeater.serialInit();
	//startSendingPthread();
	repeater.networkInit();
}

