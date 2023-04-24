#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<signal.h>


void sig_handler(int signum){
	char stop_point[5];
	printf("종료하시겠습니까?\nA) ");
	scanf("%s",stop_point);
	if(strcmp(stop_point,"exit")==0){
		printf("Process Ignore\n");
		exit(1);
	}
	else{
		printf("Signal_point Ignore, signal_handler RESET!\n");
		signal(SIGINT,SIG_DFL);
	}
}

int main(int argc,char*argv[]){
	
	signal(SIGINT,sig_handler);
	for(int i=1;;i++){
		printf("%d : Inside main function\n",i);
		sleep(1);
	}
	return 0;
}
