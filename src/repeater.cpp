#include "../inc/repeater.h"

Repeater::Repeater()
{
	std::cout<<"creating a repeater\n";
	memset(buf,0,sizeof(buf));
	length = 0;
}

Repeater::~Repeater()
{
	
	
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
