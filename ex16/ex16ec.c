#include <stdio.h>
#include <assert.h> // gives us the assert function
#include <stdlib.h> // gives us some memory functions, such as malloc, free
#include <string.h> // gives us string functions, such as strdup, strlen, and others

// Remix with no pointers

// A struct for a person
struct Person {
	char *name;
	int age;
	int height;
	int weight;
};

struct Person Person_create(char* name, int age, int height, int weight) {
	struct Person who;
	
	who.name = strdup(name);	// duplicate who->name (into dynamic memory??); then assign who->name to the duplicate (right?)
	//strcpy(who.name, name); // DO NOT use this: apparently, the scope of strcpy dies here, unless the string is created dynamically
	who.age = age;
	who.height = height;
	who.weight = weight;
	
	return who;
}


void Person_destroy(struct Person who) {	
	free(who.name); // free who->name because it was created dynamically
}


void Person_print(struct Person who) {
	printf("Name: %s\n", who.name);
	printf("\tAge: %d\n", who.age);
	printf("\tHeight: %d\n", who.height);
	printf("\tWeight: %d\n", who.weight);
}


int main(int argc, char* argv[]) {
	// Make two people structures
	struct Person joe = Person_create("Joe Alex", 32, 64, 140);
	
	// Print stuff, such as where the person exists in memory, and then the person
	printf("Joe is at memory location %p:\n", &joe); // %p prints the pointer / memory location
	Person_print(joe);
	
	struct Person frank = Person_create("Frank Blank", 20, 72, 180);
	printf("Frank is at memory location %p:\n", &frank);
	Person_print(frank);
	
	// Make everyone age 20 years, and then print them again
	joe.age += 20;
	joe.height -= 2;
	joe.weight += 40;
	Person_print(joe);
	
	frank.age += 20;
	frank.weight += 20;
	Person_print(frank);
	
	
	// Free dynamically allocated memory
	Person_destroy(joe);
	Person_destroy(frank);
	return 0;
}

