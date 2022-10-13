#include <stdio.h>
#include "202101074_header.h"
// JENIL_PATEL_202101074

int main(){
	char c;
	int n;
	printf("\nEnter a character: ");
	scanf("%c",&c);
	printf("Enter a Number: ");
	scanf("%d",&n);

	if (is_digit(c)) {
		printf("\nYou have entered a number for character!\n");
	} else {
		printf("\nYou have entered a character other than numbers!\n");
	}

	if (is_prime(n)){
		printf("You have entered a prime number!\n");
	} else {
		printf("You have entered a composite number!\n");
	}
return 0;
}

