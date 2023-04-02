#include<sys/types.h>
#include<sys/wait.h>//wait가 발생하지 않아 실행 시켜주기 위해서 사용
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

int main(int argc,char*argv[]){
	{
		pid_t pid;
		pid=fork();
		/*자식프로세서를 생성한다.*/
		fork();
		/*기존의 부모와 자식 스로세스를 한번더 발생시켜 두개의 부모와 두개의 자식프로세스를 만들어 준다.*/
		if(pid<0){
			fprintf(stderr,"fork failed");
			return 1;
		}
		/*최초로 만들어진 자식프로세스에서 파생된 새로운 자식프로세스에서 먼저 실행한다.
		이후 최초의 부모프로세스에서 만들어신 기존의 자식프로세스가 아닌 새로운 자식 프로세스에서 실행된다.*/
		else if(pid==0){
			printf("HELLO\n");
			printf("HELLO\n");
		}
		/*이후 최초의 부모프로세스와 자식프로세스였지만 fork가 발생하여 새롭게 부모가 된 프로세스에서 실행된다.*/
		else{
			wait(NULL);
			printf("HELLO\n");
		}
	}
	return 0;
}
