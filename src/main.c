#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef USE_SORT
	#include "WordPercentSort.h"
#elif USE_TABLE
	#include "WordPercentTable.h"
#elif USE_POWERSTRING
	#include "WordPercentPowerString.h"
#elif USE_POWERTABLE
	#include "WordPercentPowerTable.h"
#else
	#error "Solution flag must be specified during linking, check the Makefile.\n"
#endif

// main function which takes its inputs from the command line
int main (int argc, char **argv) {
	const char *fname;
	FILE *input_file;
	char *base_str;
	int max_length, buckets=0;

	#if !defined(USE_POWERSTRING) && !defined(USE_POWERTABLE)
		if(argc !=3) {
			printf("First input must be the base string, and second must be the txt file path.\n");
			return 0;
		}
	#else
		if(argc < 3 || argc > 4) {
			printf("First input must be the base string, and second must be the txt file path.\n");
			printf("A third, optional input may be included to set the number of hash map buckets\n");
			return 0;
		}
	#endif

	base_str=argv[1];
	fname=argv[2];
	max_length = strlen(base_str);

	#if defined(USE_POWERSTRING) || defined(USE_POWERTABLE)
		if (argc==4) {
			buckets = atoi(argv[3]);   //if invalid numeric, buckets will be set to 0 and replace in next conditional
		} 
		if (buckets <= 0) {
			buckets = (1 << (max_length+2))-1;
			printf("Invalid entry for num of hash buckets: must be a positive, non-zero integer.\n");
			printf("Defaulting to %d hash buckets",buckets);
		}
	#endif

	input_file= fopen(fname, "r");                 
	if(input_file==NULL) {                          //Prevents seg fault crash if there is a problem with the provided file
		printf("Improper file name: %s\n",fname);
		return 0;
	}

	beginSolution(base_str, input_file, max_length, buckets);

	fclose(input_file);

	return 0;
}