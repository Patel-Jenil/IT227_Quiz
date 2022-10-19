#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define	READ	0      
#define	WRITE	1    
#define length 100
#define MAX 50
#define ACK "OK"
#define child1 0
#define child2 1
#define child3 2
static int id=0;
struct query{
	int qry_id;
	char qry_text[length];
};

int main( int argc, char* argv[] )
{
	int fd[6][2];
	int pid[3];
	char buff[length+6];
	for(int i=0; i<6; i++)
		pipe(fd[i]); 
		
	pid[0] = fork();
	
	if( pid[0] != 0 )
		pid[1] = fork();
		
	
	if( pid[0] != 0 && pid[1] != 0 )
		pid[2] = fork();	
	
	if( pid[0] != 0 && pid[1] != 0 && pid[2] != 0 )	
	{
		close(fd[child1][READ]);
		close(fd[child1+3][WRITE]);
		close(fd[child2][READ]);
		close(fd[child2+3][WRITE]);
		close(fd[child3][READ]);
		close(fd[child3+3][WRITE]);
		struct query q[100];
		int cnt=0;	
		FILE* f;
		f = fopen("202101074_Quiz6_queries.txt","r");
		if( f == NULL)
		{
			fprintf(stderr,"Error: Could not open file!!\n");
			exit(0);
		}
		
		while(!feof(f))
		{
			id++;
			fscanf(f, "%d %s", &q[id].qry_id, q[id].qry_text);			
			if(q[id].qry_id > 99999 || q[id].qry_id < 0)
				continue;
			sprintf(buff, "%.5d %s", q[id].qry_id, q[id].qry_text);
			write(fd[cnt][WRITE], buff, strlen(buff)+1);
			read(fd[cnt+3][READ], buff, length);
			if(strcmp(buff,ACK) != 0){
				close(fd[child1][WRITE]);
				close(fd[child1+3][READ]);
				close(fd[child2][WRITE]);
				close(fd[child2+3][READ]);
				close(fd[child3][WRITE]);
				close(fd[child3+3][READ]);
				fclose(f);
				exit(0);
			}
			printf("Parent: Acknowledgement: %s\n\n",buff);
			cnt++;
			if( cnt == 3)
				cnt = 0;
		}	
		fclose(f);
	}
	else
	{
		int c=-1;
		if( pid[0] == 0)	c=0;
		else if( pid[1] == 0)	c=1;
		else if( pid[2] == 0)	c=2;
		else	exit(0);
		close(fd[child1][WRITE]);
		close(fd[child1+3][READ]);
		close(fd[child2][WRITE]);
		close(fd[child2+3][READ]);
		close(fd[child3][WRITE]);
		close(fd[child3+3][READ]);
		
		while(read(fd[c][READ], buff, length))
		{
			printf("Child %d: Query received: %s\n", getpid(), buff);
			write(fd[c+3][WRITE], ACK, strlen(ACK)+1);
		}
		
		close(fd[child1][READ]);
		close(fd[child1+3][WRITE]);
		close(fd[child2][READ]);
		close(fd[child2+3][WRITE]);
		close(fd[child3][READ]);
		close(fd[child3+3][WRITE]);		
	}
}
