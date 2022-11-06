#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<signal.h>
void signalHandler(){
	printf("\nI received ctrl+c!!\n");
	printf("Who cares!!!\n");
}

int main(){
	signal(SIGINT, SIG_IGN); 
	printf("Press ctrl+c!\n");
	sleep(5);
	printf("\nGot Ignored like a loser?\n");
	
	signal(SIGINT,signalHandler);
	printf("\nOk, Try once again!\n");
	sleep(5);
	printf("\n;) OOPS FAILED??\n");
	
	signal(SIGINT,SIG_DFL);
	sleep(1);
	printf("\nCome on, Don't loose the hope, Try Again\n");
	printf("This is the final one;)\n");
	sleep(1000);
}