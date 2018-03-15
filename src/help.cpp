#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <time.h>
#include <pthread.h>
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

//打印帮助信息
void help(int argc,char ** argv){
        char help[] = "--help";
        
         if ((argc == 2) && (strcmp(argv[1], help) == 0))
        {
                printf("\n");
                printf("\tUsage:\n\n");
                printf("\t");
                printf("%s", argv[0]);
                printf(" <ip address of QGroundControl>\n");
                printf("\tDefault for localhost: udp-server 127.0.0.1\n\n");
                exit(EXIT_FAILURE);
        }

}

