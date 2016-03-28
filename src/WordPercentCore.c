#include <stdio.h>
#include <string.h>
#include <stdlib.h>  
#include <stdbool.h>
#include <assert.h>

#include "WordSort.h"              // Linked only for the sorting implamentation
#include "CharTable.h"             // Linked only for the table implamentation

char *fname;
int max_length;                    // Gathered from the length of the base string

// Checks if a single char is within a string of tokenizers 
bool isTokenizer(char a) {     
	if(strchr("\n ,.!?()<>{}[]\\/",a)) {
		return true;
	} else {
		return false;
	}
}

/* opens the provided txtfile, determines indvigual word tokens, and then calls a included method (checkWord) to see
if they are formable from the base string. Finally it prints the calculated result to the command line */
void processWordsFromFile()
 {
	FILE *input_file;
	input_file= fopen(fname, "r");

	int c;                                           //character returned from fgetc
	char *c_buff;                                    //used to construct token from read characters
	int buff_index=0, word_count=0, formable_count=0;
	c_buff= (char*) calloc(max_length, sizeof(char));	
	assert(c_buff!=0);
	do{
		c = fgetc(input_file);
		if(isTokenizer(c) || c==EOF) { 			
			if(buff_index>0){	                     //non-negative index + reaching a tokenizer means c_buff contains a token
				++word_count;
				if(buff_index<=max_length) {	         //token cannot formed by the base if it is larger than the base
					formable_count+=checkWord(c_buff,buff_index);
				}		
			}
			buff_index=0;			
			memset(&c_buff[0],0,max_length);         //resets c_buff so it can be reused to build the next token
		}
		else
		{
			if(buff_index<max_length) {	
				c_buff[buff_index]=c;                //appends the current char to partial token 
			}
			++buff_index;
		}

	} while(c!=EOF);

	free(c_buff);
	fclose(input_file);
	printf("%s","Number of tokenized words read from file: ");
	printf("%d\n",word_count);
	printf("%s","Number of words formable from the base string: ");
	printf("%d\n",formable_count);
	printf("%s","Percent of formable words: ");
	printf("%.2f\n",(formable_count / (float) word_count)*100);
}

// main function which takes its inputs from the command line
int main (int argc, char **argv) {
	if(argc !=3) {
		printf("%s\n", "first input must be the base string, and second must be the txt file path");
		return 0;
	}
	char* base_str=argv[1];
	fname=argv[2];
	max_length=strlen(base_str);
	setUpBase(base_str, max_length);
	processWordsFromFile();
	cleanUpBase();
	return 0;
}