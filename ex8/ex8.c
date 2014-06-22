#include <stdio.h>

int main(int argc, char* argv[])
{
	int areas[] = {10, 12, 13, 14, 20};
	char name[] = "Zed"; // this is one way to initialize a "string"
	char full_name[] = {
		'Z','e','d',
		' ','A','.',' ',
		'S','h','a','w','\0'};

	//WARNING: On some systems, you may have to change the %ld in this code to
	//a %u (for unsigned int)
	
	// Areas
	printf("The size of an int: %ld\n", sizeof(int));
	printf("The size of areas (int[]): %ld\n", sizeof(areas));
	printf("The number of ints in the areas array: %ld\n", sizeof(areas) / sizeof(int));
	printf("The first area is %d. The 2nd area is %d.\n\n", areas[0], areas[1]);

	// Name
	printf("The size of a char: %ld\n", sizeof(char));
	printf("The size of name (char[] string): %ld\n", sizeof(name));
	printf("The number of chars in name: %ld\n\n", sizeof(name) / sizeof(char));

	// Full name
	printf("The size of full_name (char[]): %ld\n", sizeof(full_name));
	printf("The number of chars in full_name: %ld\n", sizeof(full_name) / sizeof(char));

	printf("name=\"%s\" and full_name=\"%s\"\n", name, full_name);

	// Note: The termination character in a string (in this case, '\0' counts in
	// the calculation of length.  i.e. {'A','B','C','\0'} has length 4..

	return 0;


}
