#include<stdio.h>
#include<stdlib.h>
#include<sys/time.h>
#include<limits.h>
#include<time.h>
#include<pthread.h>
#include<unistd.h>

//#define num_pthread 6
pthread_mutex_t a_lock = PTHREAD_MUTEX_INITIALIZER;
//Gettimeofday함수
double time_diff(struct timeval *start, struct timeval *end){
	return((end->tv_sec - start->tv_sec)+1e-6*(end->tv_usec - start->tv_usec));
}

double sum;
double sum2;

void *runner(void *param){
	pthread_mutex_lock(&a_lock);
	double upper=atof(param);
	for(int i=1;i<=upper;i++){
		sum+=i;
	}
	pthread_mutex_unlock(&a_lock);
	pthread_exit(0);
}

void srunner(int count, int size){
	for(int i=0;i<count;i++){
		for(int j=1;j<=size;j++){
			sum2+=j;
		}
	}
}

double do_single_thread(int run_count,int max_size){
	struct timeval start;
	struct timeval end;
	
	gettimeofday(&start,NULL);
	srunner(run_count,max_size);
	gettimeofday(&end,NULL);
	
	return time_diff(&start,&end);
}

double do_multi_thread(int num_pthread,char* max_size){
	pthread_t tid[num_pthread];

	struct timeval start;
	struct timeval end;

	gettimeofday(&start,NULL);
	for(int i=0;i<num_pthread;i++){
		printf("Multi_thread[%d] create\n",i+1);
		pthread_create(&tid[i],NULL,runner,max_size);
	}
	gettimeofday(&end,NULL);
	for(int i=0;i<num_pthread;i++){
		pthread_join(tid[i],NULL);
	}
	
	return time_diff(&start,&end);
}

void print_diff(double single_time, double multi_time){
	printf("single thread:\n");
	printf("결과:%1.lf, 소요시간:%lf\n\n",sum2,single_time);
	printf("multi thread:\n");
	printf("결과:%1.lf, 소요시간:%lf\n\n",sum,multi_time);
	printf("시간 비교:\n");
	if(single_time<multi_time){
		printf("single thread가 multi thread 대비 %.2lf배 빠르게 수행되었음.\n",(multi_time/(single_time)));
	}
	else{
		printf("multi thread가 single thread 대비 %.2lf배 빠르게 수행되었음.\n",(single_time/(multi_time)));
	}
}

int main(int argc, char*argv[]){

	double single_thread_processing_time = do_single_thread(atoi(argv[1]),atoi(argv[2]));
	double multi_thread_processing_time = do_multi_thread(atoi(argv[1]),argv[2]);
	
	print_diff(single_thread_processing_time, multi_thread_processing_time);
	return 0;
}
