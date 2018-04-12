#include "repeater.h"

Repeater::Repeater() 
	:length(0),
	 sock(0),
	 recsize(0),
	 fromlen(0),
	 bytes_sent(0),
	 temp(0)
{
	std::cout<<"creating a repeater\n";
	memset(buf,0,sizeof(buf));
}

Repeater::~Repeater()
{
	
}

int Repeater::serialInit(void){
    int ret = 0;
    ret = Open(defaultSerialPort,115200,8,NO,1);
    if(ret == 0){
        printf("open serial error!\n");
        return 0;   
    }		
    else{
        printf("open serial success!\n");
        return 1;
    }
}

int Repeater::networkInit(void){
	sock = socket(PF_INET,SOCK_DGRAM,IPPROTO_UDP);
	strcpy(target_ip,defaultTargetIP);
	
	memset(&gcAddr, 0, sizeof(gcAddr));
        gcAddr.sin_family = AF_INET;
        gcAddr.sin_addr.s_addr = inet_addr(target_ip);
	gcAddr.sin_port = htons(14550);
	
	memset(&locAddr, 0, sizeof(locAddr));
	locAddr.sin_family = AF_INET; 
	locAddr.sin_addr.s_addr = INADDR_ANY; 
	locAddr.sin_port = htons(14551); 
	
	if (-1 == bind(sock,(struct sockaddr *)&locAddr, sizeof(struct sockaddr)))
        {
                perror("error bind failed");
                close(sock);
                exit(EXIT_FAILURE);
        }
        else{
                printf("bind success\n");
        }
	
#if (defined __QNX__) | (defined __QNXNTO__)
        if (fcntl(sock, F_SETFL, O_NONBLOCK | FASYNC) < 0)
#else
        if (fcntl(sock, F_SETFL, O_NONBLOCK | O_ASYNC) < 0)
#endif

        {
                fprintf(stderr, "error setting nonblocking: %s\n", strerror(errno));
                close(sock);
                exit(EXIT_FAILURE);
        }


}

char* Repeater::getBuf()
{
	return this->buf;
}

void Repeater::setLength(int length_){
	length = length_;
}

int Repeater::getLength(void){
	return length;
}



mavlink_message_t* Repeater::getMavlinkMsg(void){
	mavlink_message_t* p;
	p = &(this->msg);
	return p;
}

mavlink_status_t* Repeater::getMavlinkStatus(void){
	mavlink_status_t* p;
	p = &(this->status);
	return p;
}

//send buf through network,using UDP protocol
int Repeater::sendBuf(void){
    sendto(sock,buf,length,0,(struct sockaddr*)&gcAddr,sizeof(struct sockaddr_in));
}

int Repeater::receiveBuf(void){
    recsize = recvfrom(sock,(void *)buf,MAX_BUF_SIZE,0,(struct sockaddr *)&gcAddr,&fromlen);
    return recsize;
}

/*
*sendToGS
*接收底板上经过串口协议发送的mavlink消息包，并经过UDP连接发送到上位机GS上的线程函数
*/
void *Repeater::sendToGS(void *ptr){

}

void *Repeater::sendToMB(void *ptr){

}

void *Repeater::sendVideo(void *ptr){

}
