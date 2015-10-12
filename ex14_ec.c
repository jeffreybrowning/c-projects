#include <stdio.h>
#include <ctype.h>
#include <string.h>

// Using Functions

/* Forward declarations
   We have to define functions that are used in the body
   of other functions so that they will exist at compiler time */

// I am assuming that the ch and arg here are the names of the params
void print_letters(char arg[], int len_args);

void print_arguments(int argc, char *argv[])
{
	for(int i = 0; i < argc; i++) {
		int len_args = strlen(argv[i]);
		print_letters(argv[i], len_args);
	}
}

void print_letters(char arg[], int len_args)
{
	for(int i = 0; i < len_args; i++) {
		char ch = arg[i];

		if(isalpha(ch) || isblank(ch)) {
			printf("'%c' == %d ", ch, ch);
		}
	}

	printf("\n");
}


int main(int argc, char *argv[]) {
	print_arguments(argc, argv);
	return 0;
}

