#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "WordSort.h"


//inputted comparision used for qsort function immediately afterward
int comparFunc(const void *a, const void *b)
{
    return *(const char *)a - *(const char *)b;
}

//alphabetizies a given string using quick sort, in to order to facilitate searching
void sortStr(char *str, int str_length) 
{
	qsort(str, str_length, sizeof(char), comparFunc);
}

/* Functions after this point are included in the header, for use in core file */

void setUpBase(char *str, int max_length) {
    base_str=str;
    sortStr(base_str, max_length);

}

void cleanUpBase() {
	//Nothing needs to be deleted here because heap memory is never allocated for the base string
}

int checkWord(char *token_str, int str_length) 
{	

	char cur_char, next_char;
	char *partial_word;                              //formed by concatinating all instances of a single char
	char *base_pointer=base_str;
	int word_index=0, partial_index, return_val=1;	
	partial_word= (char*) calloc(str_length, sizeof(char));
	assert(partial_word);
	sortStr(token_str,str_length);                   //alphabetizes the token before it is compared with the sorted base string				
	do{	
		partial_index=0;
		do{	
			cur_char= token_str[word_index];
			next_char= token_str[word_index+1];		
			partial_word[partial_index]=cur_char;    //adds each repeated char to partial_word
			++partial_index;
			++word_index;
		} while(cur_char==next_char);
		base_pointer=strstr(base_pointer, partial_word);  //Updates starting point for comparision, to reduce redundent checks
		if(!base_pointer)                            //checks if all instances of this char can be found within the base
		{
			return_val= 0;                           //result if partial_word could not be found in the base
			memset(&partial_word[0],0,str_length);  
			break;
		} else {
			memset(&partial_word[0],0,str_length);  //resets partial_word so it can collect the instances of the next char
		}
	} while(next_char!='\0');
	free(partial_word);
	return return_val;
}
