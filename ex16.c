#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

// Create a structured 
struct Person {
	char *name;
	int age;
	int height;
	int weight;
};

/* create a new structure of types in memory to represent a person
   The reason we have struct Person here is the same reason we would
   have char fart -- because this is the type of the item returned by
   this function. Person_create is therefore a function that returns a 
   pointer to the Person struct it creates. 
*/

struct Person *person_create(char *name, int age, int height, int weight) {
	/* We create a "who" person who is just as big as we need him to be.
       We do this with malloc, which allocates memory for all of the fields
       that are used in the Person structure.
	*/

	// Malloc creates structs on the "heap" using malloc instead we could do
	// struct Person who;
	struct Person *who = malloc(sizeof(struct Person));
	assert(who != NULL); /* we assert that who is not NULL, which it would be
						    if memory allocation went south */

	/* We set the properties passed in from the fuction to the actual 
       person struct using the -> symbol */
	who->name = strdup(name); // copy the value of this string into the Person
	who->age = age;
	who->height = height;
	who->weight = weight;	

	return who;
}

/* A fuction declaration returning no value which takes a Person struct as its
   only argument.*/
void person_destroy(struct Person *who)
{
	assert(who != NULL); // make sure our Person is not bad

	// if we do not free this, we get similar leakage to not destroying Persons
	// 9 bytes for Joe (8 char name with term nul byte), and 12 for Frank 
	free(who->name); // free removes the memory allocated for who's name
	free(who);  // then removes who itself?

}

// Another function that returns nothing and takes a Person
void person_print(struct Person *who) 
{
	// Prints all of the fields of Person tabbed 
	printf("Name: %s\n", who->name);
	printf("\tAge: %d\n", who->age);
	printf("\tHeight: %d\n", who->height);
	printf("\tWeight: %d\n", who->weight);
}

// The main function that will be run when the file is run from bash
int main(int argc, char *argv[])
{
	// make two Person structures and then create pointers to them 
	struct Person *joe = person_create(
		"Joe Alex", 32, 64, 140);

	struct Person *frank = person_create(
		"Frank Black", 20, 72, 180);

	// Print out where each is in memory (possible because they are lvalues)
	printf("Joe is at memory location %p:\n", joe);
	person_print(joe);

	printf("Frank is at memory location %p:\n", frank);
	person_print(frank);

	// We can do assignment to the variables we assigned for our Person struct
	joe->age += 20;
	joe->height -= 2;
	joe->weight += 40;
	person_print(joe);

	frank->age += 20;
	frank->weight += 20;
	person_print(frank);

	// Clean the structs out of memory before the program ends
	person_destroy(joe);    // valgrind shows leaked bytes if not called
	person_destroy(frank);
	//	person_destroy(NULL);  // passing NULL causes SIGABRT error

	return 0;

}
