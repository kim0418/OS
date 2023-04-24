#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include<signal.h>

void sig_handler(int signum){
	int fd;
	char * myfifo = "/tmp/myfifo";
	mkfifo(myfifo, 0666);

	char arr1[80],arr2[80];
	
        fd = open(myfifo, O_RDONLY);
        read(fd, arr1, sizeof(arr1));
        close(fd);
        int sig_command=atoi(arr1);
        switch(sig_command){
        	case SIGINT:
        		printf("(SIGINT)//");
        		printf("종료하시겠습니까?\n");
        		scanf("%s",arr2);
        		if(strcmp(arr2,"exit")==0){
        			printf("process exit\n");
        			exit(1);
        		}
        		else printf("Process Continue\n");
        		break;
        	case SIGQUIT:
        		printf("(SIGQUIT)//");
        		printf("signal_handler울 초기화하시겠습니까?(Yes/No)\n");
        		scanf("%s",arr2);
        		if(strcmp(arr2,"yes")==0 || strcmp(arr2,"Yes")==0 || strcmp(arr2,"Y")==0){
        			printf("SIgnal_Handler is Reset!\n");
        			signal(SIGINT,SIG_DFL);
        		}
        		else printf("Process Continue\n");
        		break;
        	default:
        		printf("Process Continue\n");
        }
}

int main(){
	
	signal(SIGINT,sig_handler);
	for(int i=1;;i++){
		printf("%d : Inside main function\n",i);
		sleep(1);
	}
	
	return 0;
}
