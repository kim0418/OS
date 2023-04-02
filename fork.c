#include<sys/types.h>
#include<sys/wait.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(void){
    {
	pid_t pid;
	pid = fork();
	if(pid<0){
	    fprintf(stderr,"fork failed");
	    return 1;
	}
	else if(pid==0){
		execlp("/bin/ls","ls",NULL);
	}
	else{
		wait(NULL);
		printf("child complete\n");
        }
    }
    return 0;
}
