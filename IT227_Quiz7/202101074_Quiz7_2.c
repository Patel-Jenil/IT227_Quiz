#include <signal.h>
#include <stdio.h>
#include <sys/wait.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>

void handler1() {
	printf("Handler1 is exeucted by %d\n", getpid());
}
void handler2() {
	printf("Handler2 is exeucted by %d\n", getpid());
}
void main(){
	signal(SIGINT, handler1);
	fork();
	while(1);
}
