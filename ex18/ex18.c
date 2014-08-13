#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

/** Our old friend die from ex17 */
void die (const char* message)
{
	if(errno) {
		perror(message);
	} else {
		printf("ERROR: %s\n", message);
	}
	exit(1);
}


// a typedef creates a fake type, in this
// case for a function pointer
// Typedef works like: typedef real_type my_type
// "my_type" is the type name that I want to create; real_type is the type that
// already exists in C/C++
// Here, "my_type" is a function pointer (so the function pointer is now a type)
// so, in function definitions, "compare_cb" is a function pointer, which allows
// a function parameter to be specified as a parameter to another function
typedef int (*compare_cb) (int a, int b);

/** A classic bubble sort function that uses the
* compare_cb to do the sorting.
*/
// compare_cb is a function callback - Here, the function definition accepts a
// pointer to the function that controls how the bubble_sort will sort.
int* bubble_sort(int* numbers, int count, compare_cb cmp)
{
	int temp = 0;
	int i = 0;
	int j = 0;
	
	// Dynamically allocate memory
	int* target = malloc(count * sizeof(int));
	
	if(!target) die("Memory error.");
	
	// Copy the numbers array into target
	memcpy(target, numbers, count * sizeof(int));
	
	// Commence the O(n^2) sort -- not efficient, but good for learning C
	for(i = 0; i < count; i++) {
		for(j = 0; j < count - 1; j++) {
			// cmp is a function that determines how the sorting will be
			// executed
			if( cmp(target[j], target[j+1]) > 0 ) {
				temp = target[j+1];
				target[j+1] = target[j];
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
	if (a == 0 || b == 0) {
		return 0;
	} else {
		return a % b;
	}
}


/** 
* Used to test that we are sorting things correctly
* by doing the sort and printing it out
*/

void test_sorting(int* numbers, int count, compare_cb cmp)
{
	int i = 0;
	int* sorted = bubble_sort(numbers, count, cmp);
	
	if (!sorted) die("Failed to sort as requested.");
	
	for(i = 0; i < count; i++) {
		printf("%d ", sorted[i]);
	}
	
	printf("\n");
	
	free(sorted);
}



int main(int argc, char* argv[])
{
	if(argc < 2) die ("USAGE: ex18 4 3 5 1 6");
	
	int count = argc - 1;
	
	int i = 0;
	
	char** inputs = argv + 1;
	
	int* numbers = malloc(count * sizeof(int));
	
	if(!numbers) die ("Memory error.");
	
	// Create an array using the ints from the command line
	// NOTE:  This will break if you don't use all integers
	for(i = 0; i < count; i++) {
		
		// Build the array, converting chars to int (that's what atoi does)
		numbers[i] = atoi(inputs[i]);
	}
	
	test_sorting(numbers, count, sorted_order);
	test_sorting(numbers, count, reverse_order);
	test_sorting(numbers, count, strange_order);
	
	free(numbers);
	
	return 0;
}
