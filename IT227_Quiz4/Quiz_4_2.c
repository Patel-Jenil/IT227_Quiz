#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>

void tree(char *source)
{
    struct dirent **file;
    int n = scandir(source, &file, NULL, alphasort);
    for(int i=0;i<n;i++)
    {
        if(strcmp(file[i]->d_name,".")==0 || strcmp(file[i]->d_name,"..")==0)
        {
            continue;
        }
        struct stat temp;
        stat(file[i]->d_name,&temp);
        if(S_ISDIR(temp.st_mode))
        {
            char *temp = (char*)malloc((strlen(source)+strlen(file[i]->d_name)+10)*sizeof(char));
            strcpy(temp,source);
            strcat(file[i]->d_name,"/");
            strcat(temp,file[i]->d_name);
            printf("%s\n",temp);
            tree(temp);
        }
        else
        {
            printf("%s%s\n",source,file[i]->d_name);
        }
    }
}

int main(int argc,char *argv[])
{
    tree(argv[1]);
}
