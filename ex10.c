#include <stdio.h>

int main(int argc, char *argv[])

{
	int i = 0;

	// go through each string in argv

	for(i = 0; i < argc; i++) {
		printf("arg %d: %s\n", i, argv[i]);
	}

	// let's make our own array of strings
	char *states[] = {
		"California", "Oregon", 
		"Washington", "Texas",
		NULL  // Printing out a null value prints (null)
	};

	int num_states = 5;

	for(i = 0; i < num_states; i++) {
		printf("state %d: %s\n", i, states[i]);
		printf("index 3 is: %c\n", states[i][3]);
	}

	return 0;
}

