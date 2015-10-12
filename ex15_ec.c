#include <stdio.h>

// Fun with pointers

int main(int argc, char *argv[])
{
	// create two arrays we care about
	int ages[] = {23, 43, 12, 89, 2};
	char *names[] = {"Alan", "Frank", "Mary", "John", "Lisa"};

	// safely get the size of ages
	int count = sizeof(ages) / sizeof(int);
	int i = 0;

	int *a = ages;
	char **n = names;

	// first way of using indexing
	for(i = 0; i < count; i++) {
		printf("%s has %d years alive.\n", *(n + i), *(a + i));
	}

	printf("---\n");

	// setup the pointers to the start of the arrays
	int *cur_age = ages;
	char **cur_name = names;

	// second way of using pointers
	for(i = 0; i < count; i++) {
		printf("%s is %d years old.\n", 
			   *(cur_name + i), *(cur_age + i));
	}

	printf("---\n");

	// thid way, pointers are just arrays
	for(i = 0; i < count; i++) {
		printf("%s is %d years old again.\n",
				cur_name[i], cur_age[i]);
	}

	printf("---\n");

	// sanity check -- it is impossible to print out array by assignment?
	printf("%s.\n", *names);

	printf("---\n");

	// Show how the addresses of pointers change
	for(i = 0; i < count; i++) {
		printf("%s is at address %p.\n", 
				*(cur_name + i), (cur_name + i));
		char **cur_name_lvalue = cur_name + i;
		printf("%ld difference.\n", &(cur_name_lvalue) - &cur_name);
	}


	printf("---\n");

	// fourth way whith pointers in a studpid complex way
	for(cur_name = names, cur_age = ages;
		(cur_age - ages) < count;
		 cur_name++, cur_age++)
	{
		printf("%s lived %d years so far.\n", 
				*cur_name, *cur_age);
	}

	return 0;
}

