#include <stdio.h>

int main(int argc, char *argv[]) 
{
	// go through each string in argv

	int i = 0; // Forgetting to intialize this -->
				   // use of undeclared indentifier
	while(i < argc) {
		printf("arg %d: %s\n", i, argv[i]);
		i++;
	}

	// let's make our own array of strings
	char *states[] = {
		"California", "Oregon", "Washington", "Texas"
	};

	int num_states = 4;
	i = num_states - 1; // Watch for this. i is global in the namespace, not contained
	// within the previous for loop's namespace
	while(i >= 0) {
		printf("state %d: %s\n", i, states[i]);
		i--;
	}

	return 0;
}
