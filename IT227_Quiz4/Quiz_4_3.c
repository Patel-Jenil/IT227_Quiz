#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    char buf1[11] = "abcdefghij";
    char buf2[6]= "12345";
    int fd1 = open("file1.txt", O_RDWR);
    write(fd1, buf1, 10);
    printf("*********************\n");
    printf("The content of the file :\n");
    FILE *f = fopen("file1.txt","r");
    int temp = getc(f);
    while(temp!=EOF)
    {
        printf("%c",(char)temp);
        temp = getc(f);
    }
    printf("\n");
    fclose(f);
    printf("*********************\n");
    int fd2 = open("file1.txt", O_RDWR);
    write(fd2, buf2, 5);
    printf("*********************\n");
    printf("The content of the file :\n");
    f = fopen("file1.txt","r");
    temp = getc(f);
    while(temp!=EOF)
    {
        printf("%c",(char)temp);
        temp = getc(f);
    }
    printf("\n");
    fclose(f);
    printf("*********************\n");
    int fd3 = 100;
    dup2(fd2, fd3);
    write(fd3, buf1, 5);
    printf("*********************\n");
    printf("The content of the file :\n");
    f = fopen("file1.txt","r");
    temp = getc(f);
    while(temp!=EOF)
    {
        printf("%c",(char)temp);
        temp = getc(f);
    }
    printf("\n");
    fclose(f);
    printf("*********************\n");
    close(fd1);
    close(fd2);
    close(fd3);
}
