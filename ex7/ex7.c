#include <stdio.h>

int main(int argc, char* argv[])
{
	int bugs=100;
	double bug_rate = 1.2;

	printf("You have %d bugs at the imaginary rate of %f.\n", bugs, bug_rate);

	// Messing with long ints
	long universe_of_defects = 1L * 1024L * 1024L * 1024L;
	printf("The entire universe has %ld bugs.\n", universe_of_defects);

	// Bug rate
	// Type cast here to make sure we don't get precision warnings
	double expected_bugs = bugs * bug_rate;
	printf("You are expected to have %f bugs.\n", expected_bugs);

	double part_of_universe = expected_bugs / universe_of_defects;
	printf("That is only %e portion of the universe.\n", part_of_universe);
	// Note:  %e is for double, just as %f and %f (so what are the differences???)
	// For example:  %e prints in scientific notation (but doesn't %f and other stuff?)
	
	// This next portion makes no sense (on purpose), just a demo of something weird
	char nul_byte = '\0';	// Should be 0

	int care_percentage = bugs * nul_byte;
	printf("Which means you should care %d%%.\n", care_percentage);

	// Note:  '%%' is how to print a percent sign



	printf("Side note:  This is a null byte: %c.\n", nul_byte);

	return 0;
}
