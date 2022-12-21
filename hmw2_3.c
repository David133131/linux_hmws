#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>

#define NUM_OF_THREADS 1

void* magic_num(void* arg){
  srand(time(NULL));
  int num = rand() % 500;
	*(int*)arg = num;
	return arg;
}

int main(int argc, char* argv[]){
	pthread_t ths[NUM_OF_THREADS];

	int* result = malloc(sizeof(int));

	if(pthread_create(&ths[0], NULL, &magic_num, result) != 0){
		perror("Smth went wrong");
	}



	if(pthread_join(ths[0], (void**) &result) != 0){
			perror("Smth went wrong");
	}
	
	free(result);

	printf("The magic number is equal to %d\n", *result);
	return 0;
}
