#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

pid_t pid1, pid2, pid;

void suspendChild(int n) {
	printf("Suspending child2\n");
	printf("The pid is :%d\n", pid2);
	kill(pid2, SIGSTOP);
}
void killChild() {
	printf("Killing child1\n");
	printf("The pid is :%d\n", pid1);
	kill(pid1, SIGINT);
}
void resumeChild(int n) {
	printf("Resuming child2\n");
	printf("The pid is :%d\n", pid2);
	kill(pid2, SIGCONT);
}
void childHandler() {
	printf("\nKilling parent and exiting!\n");
	kill(pid, SIGINT);
}
void killchildparent() {
	printf("Killing....\n");
	printf("Parent with pid %d and child with pid %d\n", pid, pid2);
}

int main() {
	pid1 = fork();

	if (pid1 == 0) {
		printf("Child1 pid is : %d\n", getpid());
		while (1)
			;
	} else {
		pid2 = fork();

		if (pid2 == 0) {
			printf("Child2 pid is : %d\n", getpid());
			while (1);
		} else {
			pid = getpid();
			printf("Parent pid is : %d\n", pid);

			signal(SIGALRM, suspendChild);
			alarm(2);
			pause();

			signal(SIGALRM, killChild);
			alarm(2);
			pause();

			signal(SIGALRM, resumeChild);
			alarm(1);
			pause();

			signal(SIGALRM, killchildparent);
			alarm(2);
			pause();

			kill(pid2, SIGINT);
			signal(SIGCHLD, childHandler);
		}
	}
}
