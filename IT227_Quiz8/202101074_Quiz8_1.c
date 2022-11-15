#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

struct params {
	int num1;
	int num2;
};

void *addition(void *arg) {
	struct params *thread_p = arg;
	printf("sum of numbers: %d + %d\n", thread_p->num1, thread_p->num2);
    pthread_exit(thread_p->num1+thread_p->num2);
}

int main( int argc, char* argv[] ) {
	printf("the main thread %ld has started\n", pthread_self());
	if (argc < 7)
		printf("USAGE: question1.out <num1> <num2> ...");
	int i,j=1;
	pthread_t threadID[3];
	struct params p[6];
	for(int i=1; i<argc-1; i=i+2) {	
        p[i].num1 = atoi(argv[i]);
        p[i].num2 = atoi(argv[i+1]);
	}
	for(i=1; i<argc-1; i=i+2) {	
		int err = pthread_create (&threadID[i-j], NULL, addition, (void *)&p[i]);
        if (err != 0)
            printf("cant create thread: %s\n", strerror(err));
		printf("Thread with threadID %ld is created\n",threadID[i-j]);
		j++;
	}
	for(int k=0;k<3;k++) {
		void **retval;
		pthread_join(threadID[k], &retval); 
        printf("The answer of threadID %ld is: %d\n",threadID[k],(int**)retval);
	}
	printf("the main thread %ld has terminated\n", pthread_self());
}