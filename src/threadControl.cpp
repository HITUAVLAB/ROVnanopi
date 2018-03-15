
#include "../inc/main.h"
#include "../inc/repeater.h"
#include "../inc/threadControl.h"
#include "../inc/PracticalSocket.h"
extern Repeater repeater;

//分配线程锁
pthread_mutex_t mut;

//UDP连接相关变量，设置为全局变量，以方便多线程共享
char target_ip[100];                   //地面站ip
int sock = 0;

ssize_t recsize;
socklen_t fromlen;
int bytes_sent;
unsigned int temp = 0;

struct sockaddr_in locAddr, gcAddr;

/*进行UDP网络连接的初始化*/
int networkInit(void){
	sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);    //using udp to transport the message
	strcpy(target_ip, "192.168.0.200");                          //默认ip地址
	
	memset(&gcAddr, 0, sizeof(gcAddr));
	gcAddr.sin_family = AF_INET;
	gcAddr.sin_addr.s_addr = inet_addr(target_ip);           //gcAddr 是地面站的ip
	gcAddr.sin_port = htons(14550);

	memset(&locAddr, 0, sizeof(locAddr));
	locAddr.sin_family = AF_INET;                            //IPv4网络协议套接字类型
	locAddr.sin_addr.s_addr = INADDR_ANY;                    //不管哪个ip，只要是从14551端口过来的数据，就全部进行接收
	locAddr.sin_port = htons(14551);                         //端口选择14551
	
	if (-1 == bind(sock,(struct sockaddr *)&locAddr, sizeof(struct sockaddr)))
	{
		perror("error bind failed");
		close(sock);
		exit(EXIT_FAILURE);
	}
    else{
		printf("bind success\n");
	}

        /* Attempt to make it non blocking */

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

int startSendingPthread(void){
	
	networkInit();	
	pthread_mutex_init(&mut,NULL);	
	pthread_t MBtoGS_thread , GStoMB_thread;
	int ToGS_ret = pthread_create(&MBtoGS_thread, NULL, sendToGS, NULL);
	if(ToGS_ret) {
                std::cout << "Create sendToGS pthread error!" << std::endl;
                return CREATE_SENDPTHREAD_SUCCESS;
        }
        else{
                std::cout << "Create sendToGS pthread success!" << std::endl;
        }

	int ToMB_ret = pthread_create(&GStoMB_thread, NULL, sendToMB, NULL);
        if(ToMB_ret) {
                std::cout << "Create sendToMB pthread error!" << std::endl;
                return CREATE_TOMBPTHREAD_FAILED;
        }
        else{
                std::cout << "Create sendToMB pthread success!" << std::endl;
                return CREATE_SENDPTHREAD_SUCCESS;
        }

	

	
}

void *sendToGS(void* ptr){        
	while(1){
		pthread_mutex_lock(&mut);
                repeater.setLength( repeater.Read(repeater.getBuf()) );     //length is the byte the uart read 
                if(repeater.getLength()){                                   //buf is not empty
                        for(int i = 0; i < repeater.getLength(); i++){
                                //printf("%.2X ",repeater.getBuf()[i]);
                                char target_ip[100];
				if (mavlink_parse_char(MAVLINK_COMM_0, repeater.getBuf()[i], repeater.getMavlinkMsg(), repeater.getMavlinkStatus() )){
					bytes_sent = sendto(sock, repeater.getBuf(), repeater.getLength(), 0, (struct sockaddr*)&gcAddr, sizeof(struct sockaddr_in));
				}
			}

                        //printf("%d\n",repeater.getLength());
		 }
		memset(repeater.getBuf(),0,MAX_BUF_SIZE);

		pthread_mutex_unlock(&mut);
		//usleep(20000);   //挂起20000微秒
        }//while(1)
        //pthread_join(MBtoGS_thread,NULL);       
        // Close serial port
        repeater.Close();

        return 0;


}


//建立与地面站的连接，接收来自地面站的消息包，从行为来看，这个线程是一个服务器线程
//服务器端执行流程4步入下：
//（1）调用socket函数，建立一个套接字，并用于接下来的网络通信
//（2）调用bind函数，将该套接字绑定到一个地址，并制定一个端口号
//（3）调用listen函数，使用该套接字监听连接请求 （TCP）
//（4）当请求来到时，调用accept函数复制该套接字处理请求
void *sendToMB(void* ptr){
	while(1){
		pthread_mutex_lock(&mut);
		//printf("working");
		//sleep(500);
		recsize = recvfrom(sock,(void* )repeater.getBuf(),MAX_BUF_SIZE,0,(struct sockaddr *)&gcAddr,&fromlen);
		//printf("the value of recsize:%d\n",recsize);
		if(recsize > 0){
			mavlink_message_t msg;
			mavlink_status_t status;
			
			printf("Bytes Received: %d\nDatagram: ",(int)recsize);
			for(int i = 0; i < recsize; ++i)
                        {			
                                        // Packet received
	                	printf("%.2X ",repeater.getBuf()[i]);
                                if (mavlink_parse_char(MAVLINK_COMM_0, repeater.getBuf()[i], repeater.getMavlinkMsg(), repeater.getMavlinkStatus() )){
					printf("\nReceived packet: SYS: %d, COMP: %d, LEN: %d, MSG ID: %d\n", repeater.getMavlinkMsg()->sysid, repeater.getMavlinkMsg()->compid, \
													      repeater.getMavlinkMsg()->len,   repeater.getMavlinkMsg()->msgid);
				}
        
			}
                        printf("\n");

		}
		memset(repeater.getBuf(),0,MAX_BUF_SIZE);
		pthread_mutex_unlock(&mut);

	}//while(1)


}


void *videoStreamSend(void* ptr){
	string servAddress = "192.168.0.102";
	//unsigned short servPort = Socket::resolveService("4444","udp");
}
