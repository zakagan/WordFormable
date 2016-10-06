
#include "WordFormablePowerVInts.h"

// Generates the power set from the base string, and loads the result into the hash map
void calculatePowerSet(const char *str, const unsigned int str_length, HashMap* power_set_map) {
	unsigned int i;
	Node *item=NULL, *temp_stack=NULL;
	// this stack will be populated and used to replace the need for recursive calls
	for(i=0;i<str_length;i++) {
		if (!isTokenizer(str[i])) {
			push(&temp_stack, &str[i], 1, i);
		}
	}
	// The empty string is not added to the hash table because the routine will never have to look it up
	while(temp_stack!=NULL) {
		item=pop(&temp_stack);
		hashMapUpdate(power_set_map, item->S);                  //counts the number of entries to each bin, no pushing of nodes

		for(i=item->last_index; i<str_length-1; i++){           //iterates last item through the size of the subset
			push(&temp_stack, item->S, item->length+1, i+1);
			strncat(temp_stack->S,&str[i+1],1);
		}
		destroyNode(item);	
	}
}

/* Parses the provided txtfile, determines indvigual word tokens, and then attempts to check their validity. First the token's length
 is considered, and then it is looked up within the hash map of integers. If a hash hit is found, the token is checked via the inclided 
 checkWord function. Finally the data gathered is send to the reportResults function */
void processTokensFromFile(char** base_array, const char** fname_array, const unsigned int num_inputs, const unsigned int* length_array, \
 	const unsigned int max_length, const unsigned char silence, const unsigned char tare_setup, const size_t buckets)
 {  
	unsigned int char_count, word_count, formable_count, buff_index;
	FILE *input_file;
	int c;                                             //character returned from fgetc
	char *c_buff, *copy_buff, *partial_buff;
	HashMap* power_set_map = hashMapCreate(buckets);

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
	calculatePowerSet(base_array[0], length_array[0], power_set_map);

	if(!tare_setup) {
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
						if(buff_index<=length_array[0] && checkValidityHashMap(power_set_map, c_buff)) {
							if(!silence) {
								strncpy(copy_buff, c_buff, (buff_index < max_length) ? buff_index+1 : max_length);
							}     			
							sortStr(c_buff,buff_index);      //if entry is nonempty, the string is sorted to prepare for comparing with entry strings
							if (checkWord(c_buff,base_array[0],partial_buff)) {
								formable_count++;
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
				else
				{
					if(buff_index<length_array[0]) {	
						c_buff[buff_index]=c;                //appends the current char to partial token 
					}
					++buff_index;
				}
			} while(c!=EOF);
		--char_count;		//correct for EOF being read for a char
		fclose(input_file);
		reportResults(length_array[0], char_count, word_count, formable_count);
		}
	}

	hashMapDestroy(power_set_map);
	free(partial_buff);
	if(!silence) {free(copy_buff);}
	free(c_buff);

}
