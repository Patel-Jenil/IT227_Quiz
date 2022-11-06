#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>

#define READ 0
#define WRITE 1
#define MSGLEN 1025

FILE *fChild, *fParent;
char buf1[1024], buf2[1024];
int fd1[2], bytesRead;
char buf[1024];
int i, pid1, pid2, status;

static void signal_handler(int);

int main() {
	int exit_status;
	signal(SIGUSR1, signal_handler);
	signal(SIGUSR2, signal_handler);
	pid1 = getpid();

	if ((fChild = fopen("file.txt", "r")) == NULL) {
		printf("File doesn't exist!!");
		exit(1);
	}
	if ((fParent = fopen("file2.txt", "r")) == NULL) {
		printf("File doesn't exist!!");
		exit(1);
	}
	pipe(fd1);
	pid2 = fork();
	if (pid2 == 0) {
		printf("Child pid = %d\n", getpid());
		printf("Child: sending parent SIGUSR1\n");
		while (feof(fChild) == 0) {
			fgets(buf, 1024, fChild);
			if (feof(fChild))
				break;
			strcat(buf1, buf);
		}
		printf("Data in buffer1 is \n%s\n", buf1);
		printf("Sending SIGUSR1 to parent process %d\n", pid1);
		write(fd1[WRITE], buf1, strlen(buf1) + 1);
		kill(pid1, SIGUSR1);
	} else {
		wait(&status);

		if (WIFEXITED(status)) {
			exit_status = WEXITSTATUS(status);
			if (exit_status > 128) {
				exit_status -= 256;
			}
		
			printf("Child return - %d\n", WEXITSTATUS(status));
		} else {
			if (WIFSIGNALED(status)) {
				printf("Child died on signal - %d\n", WTERMSIG(status));
			}
		}
	}
	return 0;
}

static void signal_handler(int signo) {
	switch (signo) {
	case SIGUSR1:
		printf("Process %d: received SIGUSR1 \n", getpid());
		if (pid1 == getpid()) {
			read(fd1[READ], buf1, MSGLEN);
			printf("Yes, I got data \n%s\n", buf1);
			printf("Now reading another file in parent process\n");
			while (feof(fParent) == 0) {

				fgets(buf, 1024, fParent);
				if (feof(fParent))
					break;
				strcat(buf2, buf);
			}
			printf("Data in buffer2 is \n%s\n", buf2);
			printf("Sending SIGUSR2 to child process %d\n", pid2);
			write(fd1[WRITE], buf2, strlen(buf2) + 1);
			kill(pid2, SIGUSR2);
		}
		break;

	case SIGUSR2:
		printf("Process %d: received SIGUSR2 \n", getpid());
		if (pid1 == getpid()) {
			printf("%d Condition suceeded\n", pid1);
		} else {
			read(fd1[READ], buf2, MSGLEN);
			printf("Got data \n%s\n", buf2);
			printf("Process %d will terminate itself using SIGINT\n", getpid());
			kill(getpid(), SIGINT);
		}
		break;

	default:
		break;
	}
	return;
}
