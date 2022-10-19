#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	if (argc < 2) {
		int n = 100;
		printf("Exit Status is set to: %d\n", n);
		exit(n);
	} else {
		printf("Value of argc %d\n", argc);
		exit(0);
	}
}
