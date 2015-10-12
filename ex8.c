#include <stdio.h>

int main(int argc, char *argv[])
{
	char full_name[] = {
		'Z', 'e', 'd', 
		' ', 'A', '.', ' ', 
		'S', 'h', 'a', 'w'
	};
	int areas[] = {10, 12, 13, 14, 20};
	char name[] = "Zed";

	// Warning: On some systems you may have to change the
	// %ld in this code to a %u since it will use unsigned integer

	// This is literally the memory space take up by integers
	printf("The size of an int type: %ld\n", sizeof(int));
	
	// This is the total memory space of the areas array
	printf("The size of areas (int[]): %ld\n", 
		   sizeof(areas));

	/* Since this is statically typed, we know all types in array are 
	   integers, and therefore dividing total size by size of type yields
	   number of items in array */
	printf("The number of ints in areas: %ld\n",
		   sizeof(areas)/sizeof(int));
	
	/* Shows off array indexing in C. Everything is zero indexed and works
	   similar to Python. */
	printf("The first area is %d, the 2nd is %d.\n", areas[10], areas[1]);

	// The size of a C character type with contiguous elements
	printf("The size of a char: %ld\n", sizeof(char));
	
	// The size of an array of character type values that are comma seperated
	printf("The size of name (char[]): %ld\n", sizeof(name));
	printf("The number of chars: %ld\n", sizeof(name) / sizeof(char));

	printf("The size of full_name (char[]): %ld\n", sizeof(full_name));
	printf("The number of chars: %ld\n", sizeof(full_name) / sizeof(char));

	printf("name=\"%s\" and full_name=\"%s\"\n", name, full_name);

	return 0;
}
