#include<sys/types.h>
#include<sys/wait.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

int main(int argc,char*argv[]){
	{
		pid_t pid;
		pid=fork();
		if(pid<0){
			fprintf(stderr,"fork failed");
			return 1;
		}
		else if(pid==0){
			fork();
			printf("HELLO\n");
			printf("HELLO\n");
		}
		else{
			fork();
			wait(NULL);
			printf("HELLO\n");
		}
	}
	return 0;
}
