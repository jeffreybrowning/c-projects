#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

// --- Helper functions ---

/* Our old friend die from ex17. */
void die(const char *message)
{
	if(errno) {
		perror(message);
	} else {
		printf("ERROR: %s\n", message);
	}

	// exit(1) means exit true, which exits the program
	exit(1);
}

// --- Typedefs ---

// a typedef creates a fake type, in this
// case for a function pointer with a specific call pattern which we can use as a 
// type for future sorting fuctions
typedef int (*compare_cb)(int a, int b);


// --- Sorting functions ---

/**
 * A classic bubble sort function that uses the
 * compare_cb to do the sorting
 */
int *bubble_sort(int *numbers, int count, compare_cb cmp)
{
	int temp = 0;
	int i = 0;
	int j = 0;
	int *target = malloc(count * sizeof(int));

	if(!target) die("Memory error.");

	memcpy(target, numbers, count * sizeof(int));

	// effectively a while loop that lasts long enough to check all the items in array
	for(i = 0; i < count; i++) {
		// for every item
		for(j = 0; j < count - 1; j++) {
			// if the our compare fuction returns a positive number
			if(cmp(target[j], target[j+1]) > 0) {
				// save the object on the right temporarily
				temp = target[j+1];
				// move the object on the right one to the left 
				target[j+1] = target[j];
				/* move the object on the left to the right, effectively switching the 
				   values */
				target[j] = temp;
			}
		}
	}

	return target;
}

int sorted_order(int a, int b)
{
	return a - b;
}

int reverse_order(int a, int b)
{
	return b - a;
}

int strange_order(int a, int b)
{
	if(a == 0 || b == 0) {
		return 0;
	} else {
		return a % b;
	}
}

/**
 * Used to test that we are sorting things correctly
 * by doing the sort and printing it out.
 */
void test_sorting(int *numbers, int count, compare_cb cmp)
{
	int i = 0;
	int *sorted = bubble_sort(numbers, count, cmp);

	if(!sorted) die("Failed to sort as requested.");

	for(i = 0; i < count; i++) {
		printf("%d ", sorted[i]);
	}
	printf("\n");

	free(sorted);
}

int main(int argc, char *argv[])
{
	if(argc < 2) die("USAGE: ex18 4 3 1 5 6");

	int count = argc - 1;
	int i = 0;
	char **inputs = argv + 1;

	int *numbers = malloc(count * sizeof(int));
	if(!numbers) die("Memory error.");

	for(i = 0; i < count; i++) {
		numbers[i] = atoi(inputs[i]);
	}

	/* test sorting takes as third argument a variable of type compare_cb. Since we 
     * defined with a typedef earlier our compare_cb type to take the (int a, int b) 
	 * arg pattern, we can pass a pointer to any function that has that same pattern 
     * like any of our ...order functions */
	test_sorting(numbers, count, sorted_order);
	test_sorting(numbers, count, reverse_order);
	test_sorting(numbers, count, strange_order);

	free(numbers);

	return 0;
}
