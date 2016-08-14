#include "WordFormablePartials.h"

/* parses the provided txtfile, determines indvigual word tokens, and then calls a included function (checkWord) to see
if they are formable from the base string. Finally it sends the cllected data to the reportResults function*/
void processTokensFromFile(char* base_str, FILE* input_file, char* c_buff, const unsigned int max_length, const unsigned int silence, const int buckets)
{                             
	char *partial_buff;                                         
	int char_count=0, word_count=0, formable_count=0, buff_index=0;
	int c;                                                //character returned from fgetc

	sortStr(base_str, max_length);

	partial_buff= calloc(max_length+1, sizeof(char));    //used to hold series of matching characters within a token for comparison w/ sorted base string
	if (partial_buff==NULL){
		printf("Memory allocation failed: char pointer partial_buff\n");
		exit(0);
	}

	do{
		c = fgetc(input_file);
		if(isTokenizer(c) || c==EOF) { 			
			if(buff_index>0){	                     //non-negative index + reaching a tokenizer means c_buff contains a token
				++word_count;
				char_count += buff_index;
				if(buff_index<=max_length) {	         //token cannot formed by the base if it is larger than the base
					sortStr(c_buff,buff_index);                   //alphabetizes the token before it is compared with the sorted base string				
					if (checkWord(c_buff,base_str,partial_buff,buff_index)) {
						formable_count++;
						if (!silence) {printf("%s\n",c_buff);}
					}
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

	free(partial_buff);

	reportResults(max_length, char_count, word_count, formable_count);
}
