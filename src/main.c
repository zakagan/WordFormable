#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef USE_PARTIALS
	#include "WordFormablePartials.h"
#elif USE_TABLE
	#include "WordFormableTable.h"
#elif USE_POWERSTRING
	#include "WordFormablePowerString.h"
#elif USE_POWERVINTS
	#include "WordFormablePowerVInts.h"
#elif USE_QUEUESEARCH
	#include "WordFormableQueueSearch.h"
#elif USE_BINARYSEARCH
	#include "WordFormableBinarySearch.h"
#elif USE_DAWGSEARCH
	//not implemented yet
#else
	#error "Solution flag must be specified during linking, check the Makefile.\n"
#endif

#if defined(USE_POWERSTRING) || defined(USE_POWERVINTS)
	#define NUMBER_ARGS 6	// min number of commandline arguments without including at least a second input to work on
#else
	#define NUMBER_ARGS 5
#endif

//Determines which help message to display, depending on the solution flag
int usageStatement(char* name) {
	#if defined(USE_DAWGSEARCH) 
		fprintf(stderr, "USAGE: %s base_str file1 [-silence] [-tare_setup] [base_str2 ...]\n"
			"base_str: the collection of letters used to form words from the provided dictionary\n"
			"file1: the dictionary from which words are checked for formablity from the base string\n"
			"[-silence]: default is '0', setting to '1' stops indvigual formable words from being printed to stdout\n"
			"[-tare_setup]: default is '0', setting to '1' ends the program after generating neccessary data structures\n"
			"[base_str2 ...]: additional strings to check after checking the dictionary with the intial base string\n", name);
	#elif defined(USE_POWERSTRING) || defined(USE_POWERVINTS)
		fprintf(stderr, "USAGE: %s base_str file1 [-silence] [-tare_setup] [buckets] [file2 ...]\n"
			"base_str: the collection of letters used to form words from the provided dictionary\n"
			"file1: the dictionary from which words are checked for formablity from the base string\n"
			"[-silence]: default is '0', setting to '1' stops indvigual formable words from being printed to stdout\n"
			"[-tare_setup]: default is '0', setting to '1' ends the program after generating neccessary data structures\n"
			"[buckets]: specify the number of buckets used for the hash map, must be at least '1'\n"
			"[file2 ...]: additional dictionaries to check after file1 has been completely searched\n", name);
	#else
		fprintf(stderr, "USAGE: %s base_str file1 [-silence] [-tare_setup] [file2 ...]\n"
			"base_str: the collection of letters used to form words from the provided dictionary\n"
			"file1: the dictionary from which words are checked for formablity from the base string\n"
			"[-silence]: default is '0', setting to '1' stops indvigual formable words from being printed to stdout\n"
			"[-tare_setup]: default is '0', setting to '1' ends the program after generating neccessary data structures\n"
			"[file2 ...]: additional dictionaries to check after file1 has been completely searched\n", name);
	#endif
	return 0;
}

// main function which takes its inputs from the command line
int main (int argc, char **argv) {
	char **base_array, *endptr;
	const char **fname_array;
	long int temp_long;					// used as an intermediary for reading inputs
	unsigned int num_inputs, max_length=0, *length_array;
	unsigned char silence=0, tare_setup=0;
	size_t buckets=0;

	if(argc < 3) {
		return usageStatement(argv[0]);
	}

	#if defined(USE_DAWGSEARCH)
		if(argc <= NUMBER_ARGS) {
			num_inputs=1;
			base_array= malloc(num_inputs*sizeof(char*));
			if (base_array==NULL){
				printf("Memory allocation failed: array of char pointers base_array\n");
				exit(0);
			}
			length_array= malloc(num_inputs*sizeof(int));
			if (length_array==NULL){
				printf("Memory allocation failed: array of ints length_array\n");
				exit(0);
			}
		}
		else {
			num_inputs=argc-4;
			base_array= malloc(num_inputs*sizeof(char*));
			if (base_array==NULL){
				printf("Memory allocation failed: array of char pointers base_array\n");
				exit(0);
			}
			length_array= malloc(num_inputs*sizeof(int));
			if (length_array==NULL){
				printf("Memory allocation failed: array of ints length_array\n");
				exit(0);
			}
			for (unsigned int i = 1; i < num_inputs; ++i)
			{
				base_array[i]=argv[4+i];
				length_array[i]=strlen(argv[4+i]);
				if (length_array[i] > max_length) {
					max_length=length_array[i];
				}
			}
		}
		base_array[0]=argv[1];
		length_array[0]=strlen(argv[1]);
		if (length_array[0] > max_length) {
			max_length=length_array[0];
		}
		fname_array= malloc(1*sizeof(char*));
		if (fname_array==NULL){
			printf("Memory allocation failed: array of char pointers fname_array\n");
			exit(0);
		}
		fname_array=argv[2];
	#else
		if(argc <= NUMBER_ARGS) {
			num_inputs=1;
			fname_array= malloc(num_inputs*sizeof(char*));
			if (fname_array==NULL){
				printf("Memory allocation failed: array of char pointers fname_array\n");
				exit(0);
			}
		}
		else {
			num_inputs=argc+1-NUMBER_ARGS;
			fname_array= malloc(num_inputs*sizeof(char*));
			if (fname_array==NULL){
				printf("Memory allocation failed: array of char pointers fname_array\n");
				exit(0);
			}
			for (unsigned int i = 1; i < num_inputs; ++i)
			{
				fname_array[i]=argv[(NUMBER_ARGS-1)+i];
			}
		}
		fname_array[0]=argv[2];
		base_array= malloc(1*sizeof(char*));
		if (base_array==NULL){
			printf("Memory allocation failed: array of char pointers base_array\n");
			exit(0);
		}
		base_array[0]=argv[1];
		length_array= malloc(1*sizeof(int));
		if (length_array==NULL){
			printf("Memory allocation failed: array of ints length_array\n");
			exit(0);
		}
		length_array[0]=strlen(argv[1]);
		max_length=length_array[0];
	#endif

	// This flag determines whether the found formable words are silenced or not
	if (argc >= 4) {
		endptr=NULL;
		temp_long=strtol(argv[3], &endptr, 10);
		if (!*argv[3] || *endptr || temp_long>1 || temp_long<0) {
			return usageStatement(argv[0]);
		}
		else {
			silence=temp_long;
		}
	}
	// This flag determines whether the program will end after setting up its neccessary data structures or not
	if (argc >= 5) {
		endptr=NULL;
		temp_long=strtol(argv[4], &endptr, 10);
		if (!*argv[4] || *endptr || temp_long>1 || temp_long<0) {
			return usageStatement(argv[0]);
		}
		else {
			tare_setup=temp_long;
		}
	}

	//depending on if the solution relies on a hash map, this will provide a default bucket size
	#if defined(USE_POWERSTRING) || defined(USE_POWERVINTS)
		if (argc>=6) {
			endptr=NULL;
			temp_long = strtol(argv[5], &endptr, 10);  //if invalid numeric, buckets will be set to 0 and replace in next conditional
			if (!*argv[5] || *endptr || temp_long<0) {
				return usageStatement(argv[0]);
			}
			else {
				buckets=temp_long;
			}
		}
		if (!buckets) {
			// below size_t conversion must be made to enable right shifts beyond 32 bits, essential for very long base strings
			buckets = (((size_t) 1) << (max_length+2))-1;
			if (argc==6) {
				printf("Invalid entry for num of hash buckets: must be a positive, non-zero integer.\n"
					"Defaulting to %zu hash buckets.\n",buckets);
			}
		}
	#endif

	// Process by which each solution gathers data and then sends it to be reported
	processTokensFromFile(base_array, fname_array, num_inputs, length_array, max_length, silence, tare_setup, buckets);

	free(base_array);
	free(fname_array);
	free(length_array);

	return 0;
}