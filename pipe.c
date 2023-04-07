#include<sys/types.h>
#include<sys/wait.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

#define READ 0
#define WRITE 1
#define MAX_BUF 1024

int main(int argc, char*argv[]){

	int fd[2];
	pid_t pid;
	char buf[MAX_BUF]={};
	
	if(pipe(fd)<0){
		printf("pipe error\n");
		exit(1);
	}
	else if((pid=fork())<0){
		printf("fork error\n");
		exit(1);
	}
	
	printf("\n");
	if(pid>0){
		close(fd[READ]);
		strcpy(buf,"1234");
		write(fd[WRITE],buf,strlen(buf));
		printf("Parent Process : send \"%s\" to Child\n",buf);
	}
	else{
		close(fd[WRITE]);
		read(fd[READ],buf,MAX_BUF);
		printf("Child Process : Received \"%s\" from Parent\n",buf);
	}
	exit(0);
}
