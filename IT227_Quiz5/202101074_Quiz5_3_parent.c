#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int main(int argc,char* argv[]) {
	if(argc < 6) {
		printf("Enter sufficient files!!\n");
		exit(1);
	}
	int i=0,childPID,status;
	for(i=0;i<argc-1;i++) {
		if(fork()==0) {
			printf("Calling child process %d\n",i+1);
			execl("./202101074_Quiz5_3_child.out","./202101074_Quiz5_3_child.out",argv[i+1],NULL);
			fprintf(stderr,"Could not execute %s\n",argv[i+1]);
		}
		else {
			childPID = wait(&status);
			printf("Child with PID=%d finished\n", childPID);
		}
	}
}