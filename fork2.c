#include<sys/types.h>
#include<sys/wait.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int data=500;

int main(int argc, char*argv[]){
    int *heap=malloc(sizeof(int));
    int stack=10;
    int statloc;
    int pid;
    int fd[2];

    pipe(fd);

    pid=fork();
    if(pid==0){
	stack=30;
	*heap=50;
	data=1000;
	printf("child stack: %d %p\n",stack, &stack);
	printf("child heap: %d %p\n", *heap,heap);
	printf("child data: %d %p\n", data,&data);
	printf("chlid pipe: %d %p\n", fd[0],&fd[0]);
    }
    else{
	wait(&statloc);
	printf("parent stack: %d %p\n",stack, &stack);
	printf("parent heap: %d %p\n", *heap,heap);
	printf("parent data: %d %p\n", data,&data);
	printf("parent pipe: %d %p\n", fd[0],&fd[0]);
    }
    free(heap);
    exit(0);
}
