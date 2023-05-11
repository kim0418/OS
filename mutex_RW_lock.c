#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<string.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/time.h>
#include<time.h>

#define MAX_SIZE 1024

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t rw_mutex = PTHREAD_MUTEX_INITIALIZER;

double time_diff(struct timeval *start, struct timeval *end){
	return((end->tv_sec - start->tv_sec)+1e-6*(end->tv_usec - start->tv_usec));
}

char* shared_memory[100];
int read_counter=1;
int rd_counter=0;

void* write_process(void*arg){
	pthread_mutex_lock(&rw_mutex);
	
	char* wt_arr=(char*)malloc(sizeof(char)*MAX_SIZE);
	printf("Writing....\n>>>");
	scanf("%s",wt_arr);
	strncpy(shared_memory,wt_arr,sizeof(wt_arr+1));
	
	pthread_mutex_unlock(&rw_mutex);
}

void* read_process(void*arg){
	pthread_mutex_lock(&mutex);
	rd_counter++;
	if(rd_counter==1){
		pthread_mutex_lock(&rw_mutex);
	}
	pthread_mutex_unlock(&mutex);
	
	char*file_name=(char*)malloc(sizeof(char)*MAX_SIZE);
	char*rd_arr=(char*)malloc(sizeof(char)*MAX_SIZE);
	strncpy(rd_arr,shared_memory,sizeof(shared_memory+1));
	sprintf(file_name,"Thread_Reader-%d.txt",read_counter);
	FILE*fd=fopen(file_name,"a");
	fprintf(fd,"%s\n",rd_arr);
	if(strcmp(shared_memory,"exit")==0){
		fclose(fd);
		printf("EXIT\n");
		exit(1);
	}
	fclose(fd);
	read_counter++;
	
	pthread_mutex_lock(&mutex);
	rd_counter--;
	if(rd_counter==0){
		pthread_mutex_unlock(&rw_mutex);
	}
	pthread_mutex_unlock(&mutex);
}

int main(int argc, char*argv[]){

	pthread_t pc_core[20];
	
	struct timeval start;
	struct timeval end;
	
	do{
		pthread_create(&pc_core[0],NULL,write_process,NULL);
		gettimeofday(&start,NULL);
		for(int i=1;i<20;i++){
			pthread_create(&pc_core[i],NULL,read_process,NULL);
		}
		gettimeofday(&end,NULL);
		for(int i=0;i<20;i++){
			pthread_join(pc_core[i],NULL);
		}
		read_counter=1;
		printf("Run_Time : %lf\n",time_diff(&start,&end));
	}while(1);

	return 0;
}
