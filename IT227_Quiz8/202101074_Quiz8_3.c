#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include<fcntl.h>
#include <sys/wait.h>

#define READ 0
#define WRITE 1

int fd1[2],fd2[2];
FILE *fcp;
FILE *fpc;

void *childread() {
	int byteread;
    char msg[256];
    byteread=read(fd1[READ],msg,256);
    printf("child reads: %s\n",msg);
}

void *parentread() {
	int byteread;
    char msg[256];
    byteread=read(fd2[READ],msg,256);
    printf("parent reads: %s\n",msg);
}

int main() {
	int status;
	fcp=fopen("child.txt","r+");
	fpc=fopen("parent.txt","r+");
	pipe(fd1); 
	pipe(fd2); 
	if(fork()==0) {
		close(fd1[WRITE]);
		close(fd2[READ]);
		while(fgetc(fcp)!=EOF) {
            int rdom=rand()%5;
            pthread_t thread;
            pthread_create(&thread,NULL,childread,NULL);
            sleep(1);
            char buf[256];
            fgets(buf,256,fcp);
			for(int u=0;u<rdom;u++)
                sleep(1);
			printf("child writes: %s\n",buf);
            write(fd2[WRITE],buf,strlen(buf)+1);
		}
		close(fd1[READ]);
		close(fd2[WRITE]);
	} else {
		close(fd1[READ]);
		close(fd2[WRITE]);
		while(fgetc(fpc)!=EOF) {
			pthread_t thread1;
            pthread_create(&thread1,NULL,parentread,NULL);
            sleep(1);
            int rdom=rand()%5;
            char buff[256];
            fgets(buff,256,fpc);
            for(int u=0;u<rdom;u++)
                sleep(1);
			printf("parent writes: %s\n",buff);
			write(fd1[WRITE],buff,strlen(buff)+1);
		}
		close(fd1[WRITE]);
		close(fd2[READ]);
		wait(&status);
	}
	return 0;
}