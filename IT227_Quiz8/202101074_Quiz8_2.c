#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <pthread.h>

int arrIP[100];

void *Insertsort(void *arg) {
	printf("\nthread id %u is starting \n", (unsigned int)pthread_self());
	int *k = arg;
	for (int i = (*k + 1); i < (*k + 25); i++) {
		int tp = arrIP[i], j = i - 1;
		while (j >= *k && tp < arrIP[j]) {
			arrIP[j + 1] = arrIP[j];
			j--;
		}
		arrIP[j + 1] = tp;
	}
	for(int i = (*k + 1); i < (*k + 25); i++) {
		printf("%d ",arrIP[i]);
	}
	printf("\nthread id %u is exiting \n", (unsigned int)pthread_self());
}

int main(int argc, char *argv[]) {
	int j;
	pthread_t threadID1,threadID2,threadID3,threadID4;
	for(int i=0;i<100;i++) {
		arrIP[i]=rand() % 100;
	}
	int arr[4]={0,25,50,75};
	pthread_create(&threadID1, NULL, Insertsort, (void *)&arr[0]);
	pthread_create(&threadID2, NULL, Insertsort, (void *)&arr[1]);
	pthread_create(&threadID3, NULL, Insertsort, (void *)&arr[2]);
	pthread_create(&threadID4, NULL, Insertsort, (void *)&arr[3]);
	pthread_join(threadID1,NULL);
	pthread_join(threadID2,NULL);
	pthread_join(threadID3,NULL);
	pthread_join(threadID4,NULL);
	printf("the main thread has terminated\n", pthread_self());
}
