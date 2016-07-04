#include "WordPercentSort.h"

/* Takes an alphabetized word and an alphabetized base string
returns 1 if the word can be formed from the base string, 0 otherwise */
int checkWord(const char *token_str, const int str_length) 
{	

	char cur_char, next_char;
	char *base_pointer=base_str;
	int word_index=0, partial_index, return_val=1;	
	do{	
		partial_index=0;
		do{	
			cur_char= token_str[word_index];
			next_char= token_str[word_index+1];		
			partial_buff[partial_index]=cur_char;    //adds each repeated char to partial_buff
			++partial_index;
			++word_index;
		} while(cur_char==next_char);
		base_pointer=strstr(base_pointer, partial_buff);  //Updates starting point for comparision, to reduce redundent checks
		memset(&partial_buff[0],0,str_length * sizeof(char));  //resets partial_buff so it can collect the instances of the next char
		if(!base_pointer)                            //checks if all instances of this char can be found within the base
		{
			return_val= 0;                           //result if partial_buff could not be found in the base
			break;
		}
	} while(next_char!='\0');
	return return_val;
}

/* opens the provided txtfile, determines indvigual word tokens, and then calls a included method (checkWord) to see
if they are formable from the base string. Finally it prints the calculated result to the command line */
void processWordsFromFile(FILE* input_file, const int max_length)
{                             
	char* c_buff;                                         
	int char_count=0, word_count=0, formable_count=0, buff_index=0;
	int c;                                                //character returned from fgetc

	c_buff= calloc(max_length, sizeof(char));	    //used to build word tokens as read from the provided file
	assert(c_buff);

	do{
		c = fgetc(input_file);
		if(isTokenizer(c) || c==EOF) { 			
			if(buff_index>0){	                     //non-negative index + reaching a tokenizer means c_buff contains a token
				++word_count;
				char_count += buff_index;
				if(buff_index<=max_length) {	         //token cannot formed by the base if it is larger than the base
					sortStr(c_buff,buff_index);                   //alphabetizes the token before it is compared with the sorted base string				
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
	reportResults(max_length, char_count, word_count, formable_count);
}

void beginSolution(char* provided_base_str,FILE* input_file, const int max_length, const int buckets) {

	base_str=provided_base_str;
	sortStr(base_str, max_length);
	
	partial_buff= calloc(max_length, sizeof(char));    //used to hold series of matching characters within a token for comparison w/ sorted base string
	assert(partial_buff);       

	processWordsFromFile(input_file, max_length);

	free(partial_buff);
}