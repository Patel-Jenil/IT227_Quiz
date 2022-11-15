#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <semaphore.h>
#include <signal.h>
#include <pthread.h>

#define READ 0
#define WRITE 1

sem_t semaphore[2];
int fd1[2], fd2[2], pid;
void handler2();
void handler1() {
	char buf[256];
	read(fd1[READ], buf, 256);
	printf("received 1: %s\n", buf);
}

void handler2() {
	char buf2[256];
	read(fd2[READ], buf2, 256);
	printf("received 2: %s\n", buf2);
}

void handler3() {
	kill(pid, SIGINT);
}
void *communicate1() {
	char buffer[] = "communicate to thread ";
	printf("%ld entering in pipe 1\n", pthread_self());
	sem_wait(&semaphore[0]);
	int p = pthread_self() % 10;
	char s[2];
	s[0] = p + '0';
	s[1] = '\0';
	strcat(buffer, s);
	write(fd1[WRITE], buffer, strlen(buffer) + 1);
	kill(pid, SIGUSR1);
	sleep(1);
	sem_post(&semaphore[0]);
	pthread_exit(0);
}

void *communicate2() {
	char buffer2[] = "communicate to thread ";
	printf("%ld entering in pipe 2\n", pthread_self());
	sem_wait(&semaphore[1]);
	int p = pthread_self() % 10;
	char s[2];
	s[0] = p + '0';
	s[1] = '\0';
	strcat(buffer2, s);
	write(fd2[WRITE], buffer2, strlen(buffer2) + 1);
	kill(pid, SIGUSR2);
	sleep(1);
	sem_post(&semaphore[1]);
	pthread_exit(0);
}

int main() {
	pipe(fd1);
	pipe(fd2);
	pid = getpid();
	signal(SIGUSR1, handler1);
	signal(SIGUSR2, handler2);
	if (fork() == 0) {
		close(fd1[READ]);
		close(fd2[READ]);
		sem_init(&semaphore[0], 0, 1);
		sem_init(&semaphore[1], 0, 1);
		pthread_t t[6];
		for (int i = 0; i < 3; i++) {
			pthread_create(&t[i], NULL, communicate1, NULL);
		}
		for (int i = 3; i < 6; i++) {
			pthread_create(&t[i], NULL, communicate2, NULL);
		}
		for (int i = 0; i < 6; i++) {
			pthread_join(t[i], NULL);
		}
		close(fd1[WRITE]);
		close(fd2[WRITE]);
	} else {
		close(fd1[WRITE]);
		close(fd2[WRITE]);
		signal(SIGCHLD, handler3);
		int i = 3;
		while (1)
			;
		close(fd1[READ]);
		close(fd2[READ]);
		return 0;
	}
}
