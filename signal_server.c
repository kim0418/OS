#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include<signal.h>

int main()
{
    int fd1;

    char * myfifo = "/tmp/myfifo";
	
    mkfifo(myfifo, 0666);

    char str1[80], str2[80];
    printf(" 2) Eixt(SIGINT) 3) Signal_reset(SIGQUIT)\n");
    while (1){
	printf("입력대기\n");
        fd1 = open(myfifo,O_WRONLY);
        fgets(str2, 80, stdin);
        
        write(fd1, str2, strlen(str2)+1);
        if(strcmp(str2,"exit\n")==0){
        	close(fd1);
        	break;
        }
        close(fd1);
    }
    return 0;
}

