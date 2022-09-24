#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    char *s = argv[1];
    link(s,"./hard_by_code");
    symlink(s,"./soft_by_code");
}
