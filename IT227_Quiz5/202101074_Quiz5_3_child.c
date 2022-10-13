#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>

int main(int argc,char* argv[]) {
	if(argc<2) {
		printf("Provide sufficient files!!\n");
		exit(1);
	}
	printf("Running who command on %s",argv[1]);
	execlp("wc","wc",argv[1],NULL);
}