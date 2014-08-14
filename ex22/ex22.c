#include <stdio.h>
#include "ex22.h"
#include "dbg.h"

// THE_SIZE is actually an extern int, so it is accessible to other c files
int THE_SIZE = 1000;

// "static" means that the variable is accessible to all functions, but only in this file
static int THE_AGE = 37;

int get_age()
{
	// this return statement works because THE_AGE is static, and it was defined in the .h file 
	// (which means it is accessible to the
	// scope of all the functions in this file
	return THE_AGE;
}

void set_age(int age)
{
	THE_AGE = age;
}

double update_ratio(double new_ratio)
{
	// Static variables defined inside a function maintain their value between
	// function calls
	static double ratio = 1.0;

	double old_ratio = ratio;
	ratio = new_ratio;

	return old_ratio;
}

void print_size()
{
	log_info("I think size is: %d", THE_SIZE);
}

