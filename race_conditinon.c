#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<string.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/time.h>
#include<time.h>

pthread_mutex_t a_lock = PTHREAD_MUTEX_INITIALIZER;

double sum;
double locking_sum;

void *runner(void *param){
	double upper=atof(param);
	for(int i=1;i<=upper;i++){
		sum+=i;
	}
	pthread_exit(0);
}

void *locking_runner(void *param){
	pthread_mutex_lock(&a_lock);
	double upper=atof(param);
	for(int i=1;i<=upper;i++){
		locking_sum+=i;
	}
	pthread_mutex_unlock(&a_lock);
	pthread_exit(0);
}


double do_multi_thread(int num_pthread,char* max_size){
	pthread_t tid[num_pthread];

	for(int i=0;i<num_pthread;i++){
		pthread_create(&tid[i],NULL,runner,max_size);
	}
	for(int i=0;i<num_pthread;i++){
		pthread_join(tid[i],NULL);
	}
}

double do_locking_multi_thread(int num_pthread,char* max_size){
	pthread_t tid[num_pthread];

	for(int i=0;i<num_pthread;i++){
		pthread_create(&tid[i],NULL,locking_runner,max_size);
	}
	for(int i=0;i<num_pthread;i++){
		pthread_join(tid[i],NULL);
	}
}

void print_diff(char*thread_num){
	printf("[%1.lf]개 core가진 Thread의 연산 합 : %1.lf\n",atof(thread_num),sum);
	printf("[%1.lf]개 core가진 Lcoking_Thread의 연산 합 : %1.lf\n",atof(thread_num),locking_sum);
}

int main(int argc, char* argv[]){
	do_multi_thread(atoi(argv[1]),argv[2]);
	do_locking_multi_thread(atoi(argv[1]),argv[2]);
	print_diff(argv[1]);
	return 0;
}
