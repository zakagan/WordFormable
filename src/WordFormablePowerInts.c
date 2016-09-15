
#include "WordFormablePowerInts.h"

// Generates the power set from the base string, and loads the result into the hash map
void calculatePowerSet(const char *str, const int str_length, HashMap* power_set_map) {
	int i;
	Node *item=NULL, *temp_stack = NULL;
	// this stack will be populated and used to replace the need for recursive calls
	for(i=0;i<str_length;i++) { 
		push(&temp_stack, &str[i], 1, i);
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
void processTokensFromFile(char* base_str, FILE* input_file, char* c_buff, char* copy_buff, unsigned const int max_length, unsigned const int silence, const size_t buckets) 
 {  
	int char_count=0, word_count=0, formable_count=0, buff_index=0;
	int c;                                             //character returned from fgetc
	char* partial_buff;
	HashMap* power_set_map = hashMapCreate(buckets); 

	partial_buff= calloc(max_length, sizeof(char));    //used to hold series of matching characters within a token for comparison w/ sorted base string
	if (partial_buff==NULL){
		printf("Memory allocation failed: char pointer partial_buff\n");
		exit(0);
	}

	sortStr(base_str, max_length);
	calculatePowerSet(base_str, max_length, power_set_map);

	do{
		c = fgetc(input_file);
		if(isTokenizer(c) || c==EOF) { 			
			if(buff_index>0){	                     //non-negative index + reaching a tokenizer means c_buff contains a token
				++word_count;
				char_count += buff_index;
				if(buff_index<=max_length && checkValidityHashMap(power_set_map, c_buff)) {
					if(!silence) {strncpy(copy_buff, c_buff, max_length);}        			
					sortStr(c_buff,buff_index);      //if entry is nonempty, the string is sorted to prepare for comparing with entry strings
					if (checkWord(c_buff,base_str,partial_buff,buff_index)) {
						formable_count++;
						if (!silence) {printf("\t%s\n",copy_buff);}
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

	hashMapDestroy(power_set_map);
	free(partial_buff);
	
	reportResults(max_length, char_count, word_count, formable_count);
}
