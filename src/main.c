#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef USE_SORT
	#include "WordPercentSort.h"
#elif USE_TABLE
	#include "WordPercentTable.h"
#elif USE_POWERSTRING
	#include "WordPercentPowerString.h"
#elif USE_POWERINTS
	#include "WordPercentPowerInts.h"
#else
	#error "Solution flag must be specified during linking, check the Makefile.\n"
#endif

// main function which takes its inputs from the command line
int main (int argc, char **argv) {
	const char *fname;
	FILE *input_file;
	char *base_str, *c_buff;
	int max_length, buckets=0, silence=0;

	//Determines which help message to display, depending on the solution flag
	#if !defined(USE_POWERSTRING) && !defined(USE_POWERINTS)
		if(argc < 3 || argc > 4) {
			printf("Two inputs are required: 1st the base string, and 2nd the path to your text file.\n"
				"Optionally, you may silence formable word printing by adding the integer '1' as a 3rd input.\n"
				"An example of properly formatted inputs: \n"
				"%s helloworld examples_files/example.txt 1\n", argv[0]);
			return 0;
		}
	#else
		if(argc < 3 || argc > 5) {
		printf("Two inputs are required: 1st the base string, and 2nd the path to your text file.\n"
				"Optionally, you may silence formable word printing by adding the integer '1' as a 3rd input.\n"
				"As another, optional input you can specify the number of hash buckets to be used.\n"
				"An example of properly formatted inputs: \n"
				"%s helloworld examples_files/example.txt 1 63\n", argv[0]);
			return 0;
		}
	#endif

	base_str=argv[1];                               //the base string from which a token's "formablity" is based
	fname=argv[2];									// the provided text file name
	max_length = strlen(base_str);

	c_buff= calloc(max_length, sizeof(char));	    //used to build word tokens as read from the provided file
	if (c_buff==NULL){
		printf("Memory allocation failed: char pointer c_buff\n");
		exit(0);
	}	

	// This flag determines whether the found formable words are silenced or not
	if (argc >= 4) {
		silence=atoi(argv[3]);
	} 

	//depending on if the solution relies on a hash map, this will provide a default bucket size
	#if defined(USE_POWERSTRING) || defined(USE_POWERINTS)
		if (argc==5) {
			buckets = atoi(argv[4]);   //if invalid numeric, buckets will be set to 0 and replace in next conditional
		} 
		if (buckets <= 0) {
			buckets = (1 << (max_length+2))-1;
			if (argc==5) {
				printf("Invalid entry for num of hash buckets: must be a positive, non-zero integer.\n"
					"Defaulting to %d hash buckets",buckets);
			}
		}
	#endif

	input_file= fopen(fname, "r");                 
	if(input_file==NULL) {                          //Prevents seg fault crash if there is a problem with the provided file
		printf("Improper file name: %s\n",fname);
		exit(0);
	}

	// Process by which each solution gathers data and then sends it to be reported
	processTokensFromFile(base_str, input_file, c_buff, max_length, silence, buckets);

	free(c_buff);
	fclose(input_file);

	return 0;
}