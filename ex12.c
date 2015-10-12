#include <stdio.h>

int main(int argc, char *argv[]) 
{
	int i = 0;
	int arg_sans = argc - 1;

	if(arg_sans == 1) {
		printf("You only have one argument. You suck.\n");
	} else if(arg_sans > 1 && arg_sans < 4) {
		printf("Here's your arguments:\n");

		for(i = 0; i < argc; i++) {
			printf("%s ", argv[i]);
		}

		printf("\n");
	} else {
		printf("You have too many arguements. You suck.\n");
	}
	
	return 0;

}
