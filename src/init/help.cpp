#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

