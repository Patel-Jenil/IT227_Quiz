#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main()
{
    struct stat first;
    
    printf("***************************************\n");
    stat("./test.txt",&first);
    printf("Data for \"./test.txt\"\n");
    printf("The i-node number of this file is %lu\n",first.st_ino);
    printf("***************************************\n");
    stat("./Quiz_4_1.c",&first);
    printf("Data for \"./Quiz_4_1.c\"\n");
    printf("The i-node number of this file is %lu\n",first.st_ino);
    printf("***************************************\n");
    stat("./hard_by_code",&first);
    printf("Data for \"./hard_by_code\"\n");
    printf("The no. of hard link associated with it is : %lu\n",first.st_nlink);
    printf("The i-node number of this file is %lu\n",first.st_ino);
    printf("***************************************\n");
    stat("./hard_by_command",&first);
    printf("Data for \"./hard_by_command\"\n");
    printf("The no. of hard link associated with it is : %lu\n",first.st_nlink);
    printf("The i-node number of this file is %lu\n",first.st_ino);
    printf("***************************************\n");
    lstat("./soft_by_code",&first);
    printf("Data for \"./soft_by_code\"\n");
    printf("The no. of hsoft link associated with it is : %lu\n",first.st_nlink);
    printf("The i-node number of this file is %lu\n",first.st_ino);
    printf("***************************************\n");
    lstat("./soft_by_command",&first);
    printf("Data for \"./soft_by_command\"\n");
    printf("The no. of soft link associated with it is : %lu\n",first.st_nlink);
    printf("The i-node number of this file is %lu\n",first.st_ino);
    printf("***************************************\n");
}
