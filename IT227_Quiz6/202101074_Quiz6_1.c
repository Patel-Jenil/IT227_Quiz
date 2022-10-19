#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define	READ 0       
#define	WRITE 1      
#define LEN 1024
#define MAX 50
#define ACK "OK"

struct query {
	int qry_id;
	char qry_text[MAX];
};

int main( int argc, char* argv[] )
{
	int fd1[2];		//Parent Writer, Child Reader
	int fd2[2];		//Parent Reader, Child Writer
	int pid,status;
	char msge[LEN];
	pipe(fd1);
	pipe(fd2);	
	printf("Enter 0 to Exit!!\n");
	pid = fork();
	if( pid == 0 )		//Child
	{
		close(fd1[WRITE]);
		close(fd2[READ]);
		
		while(read(fd1[READ], msge, LEN))
		{
			printf("Child: Query received: %s\n", msge);
			write(fd2[WRITE], ACK, strlen(ACK)+1);
		}
		
		close(fd1[READ]);
		close(fd2[WRITE]);
	}
	else				//Parent
	{
		close(fd1[READ]);
		close(fd2[WRITE]);
		struct query q;
		do
		{
			printf("\nEnter query details!!\n");
			printf("Query ID: ");
			scanf("%d", &q.qry_id);
			if(q.qry_id > 99999 || q.qry_id < 0)
			{
				printf("Enter Query ID from 0 to 99999\n");
				continue;
			}
			if( q.qry_id == 0)
			{
				strcpy(q.qry_text, "EXIT!");
			}
			else
			{
				getchar();
				printf("Query: ");
				scanf("%[^\n]%*c", q.qry_text);
			}
			//copy to buffer
			sprintf(msge, "%.5d %s", q.qry_id, q.qry_text);
			write(fd1[WRITE], msge, strlen(msge)+1);
			read(fd2[READ], msge, LEN);
			if(strcmp(msge,ACK) != 0){
				close(fd1[WRITE]);
				close(fd2[READ]);
				exit(0);
			}
			printf("Parent: Acknowledgement: %s\n",msge);
		} while(q.qry_id != 0);
		
	}
}