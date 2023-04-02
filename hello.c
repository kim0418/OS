#include<sys/types.h>
#include<sys/wait.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

void print(int count, char*s){
	for(int i=0;i<count;i++){
		printf("%s\n",s);
	}
}

int system_call(char*s){
	{
		pid_t pid;
		pid=fork();
		if(pid<0){
			fprintf(stderr,"fork failed");
			return 1;
		}
		else if(pid==0){
			print(strlen(s),s);
		}
		else{
			wait(NULL);
			printf("HELLO\n");
		}
	}
	return 0;
}

int main(int argc, char*argv[]){
	system_call("HELLO");
}
