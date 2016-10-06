#include "WordFormablePartials.h"

/* parses the provided txtfile, determines indvigual word tokens, and then calls a included function (checkWord) to see
if they are formable from the base string. Finally it sends the cllected data to the reportResults function*/
void processTokensFromFile(char** base_array, const char** fname_array, const unsigned int num_inputs, const unsigned int* length_array, \
 	const unsigned int max_length, const unsigned char silence, const unsigned char tare_setup, const size_t buckets)
{                             
	char *c_buff, *copy_buff, *partial_buff;
	FILE *input_file;                                
	unsigned int char_count, word_count, formable_count, buff_index;
	int c;                                                //character returned from fgetc

	c_buff= calloc(max_length+1, sizeof(char));		//used to build word tokens as read from the provided file
	if (c_buff==NULL){
		printf("Memory allocation failed: char pointer c_buff\n");
		exit(0);
	}

	if(!silence) {
		copy_buff=calloc(max_length+1, sizeof(char));		// used to hold unsorted word tokens for reporting on unsilenced calls
		if (copy_buff==NULL) {
			printf("Memory allocation failed: char pointer copy_buff\n");
			exit(0);
		}
	}
	partial_buff= calloc(max_length, sizeof(char));    //used to hold series of matching characters within a token for comparison w/ sorted base string
	if (partial_buff==NULL){
		printf("Memory allocation failed: char pointer partial_buff\n");
		exit(0);
	}

	sortStr(base_array[0], length_array[0]);               
	//in this case the first value in the length array == max_length, in the main loop the value in length array is preferred in just case of future changes

	if (!tare_setup) {
		for(unsigned int i=0; i<num_inputs; ++i) {
			char_count=0, word_count=0, formable_count=0, buff_index=0;

			input_file= fopen(fname_array[i], "r");                 
			if(input_file==NULL) {                          //Prevents seg fault crash if there is a problem with the provided file
				printf("Improper file name: %s\n",fname_array[i]);
				continue;
			}

			if(!silence) {
				displayIntro(i+1,fname_array[i]);
			}

			do{
				c = fgetc(input_file);
				if(isTokenizer(c) || c==EOF) { 			
					if(buff_index>0){	                     //non-negative index + reaching a tokenizer means c_buff contains a token
						++word_count;
						char_count += buff_index+1;			// +1 to account for the tokenizing character causing termination of token reading 
						if(buff_index<=length_array[0]) {	         //token cannot formed by the base if it is larger than the base
							if(!silence) {
								strncpy(copy_buff, c_buff, (buff_index < max_length) ? buff_index+1 : max_length);
							}
							sortStr(c_buff,buff_index);                   //alphabetizes the token before it is compared with the sorted base string				
							if (checkWord(c_buff,base_array[0],partial_buff)) {
								++formable_count;
								if (!silence) {printf("\t%s\n",copy_buff);}
							}
						}
						 //reset params for next loop and next token  
						memset(&c_buff[0],0,(buff_index < max_length) ? buff_index : max_length);
						buff_index=0;	
					}					
					else {
						++char_count;		// A tokenizer char has been found, but no token is being formed
					}	 						
				}
				else {
					if(buff_index<length_array[0]) {	
						c_buff[buff_index]=c;                //appends the current char to token 
					}
					++buff_index;
				}

			} while(c!=EOF);
			--char_count;		//correct for EOF being read for a char
			fclose(input_file);
			reportResults(length_array[0], char_count, word_count, formable_count);
		}
	}

	free(partial_buff);
	if(!silence) {free(copy_buff);}
	free(c_buff);
}
