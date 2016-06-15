
#include "WordPercentPowerString.h"

void calculatePowerSet(char *str, int str_length) {
	int i;
	Node *item=NULL, *temp_stack = NULL;
	// this stack will be populated and used to replace the need for recursive calls
	for(i=0;i<str_length;i++) { 
		push(&temp_stack, &str[i], 1, i);
	}
	// The empty string is not added to the hash table because the routine will never have to look it up
	//printf("Calculating Power Set...\n");
	while(temp_stack!=NULL) {
		item=pop(&temp_stack);
		hashMapInsert(power_set_map, item);
		//printf("Inserted to hash map: %s\n", item->S);

		for(i=item->last_index; i<str_length-1; i++){           //iterates last item through the size of the subset
			push(&temp_stack, item->S, item->length+1, i+1);
			strncat(temp_stack->S,&str[i+1],1);
		}
		destroyNode(item);	
	}
	//printf("Power Set calculation complete\n");
}

/* opens the provided txtfile, determines indvigual word tokens, and then calls a included method (checkWord) to see
if they are formable from the base string. Finally it prints the calculated result to the command line */
void processWordsFromFile(char *fname, int max_length)
 {
	FILE* input_file;      
	char* c_buff;
	Node* temp_stack;
	int word_count=0, formable_count=0, buff_index=0;
	int c;                                             //character returned from fgetc

	c_buff= calloc(max_length, sizeof(char));	//used to build word tokens as read from the provided file
	assert(c_buff);

	input_file= fopen(fname, "r");
	do{
		c = fgetc(input_file);
		if(isTokenizer(c) || c==EOF) { 			
			if(buff_index>0){	                     //non-negative index + reaching a tokenizer means c_buff contains a token
				++word_count;
				if(buff_index<=max_length) {	         //token cannot formed by the base if it is larger than the base            			
					temp_stack = collectHashMapEntry(power_set_map, c_buff, buff_index);
					if (temp_stack) {
						sortStr(c_buff,buff_index);      //if entry is nonempty, the string is sorted to prepare for comparing with entry strings
						formable_count+=checkStackForString(temp_stack, c_buff, buff_index);
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

	fclose(input_file);
	free(c_buff);
	reportResults(word_count, formable_count);
}

// main function which takes its inputs from the command line
int main (int argc, char **argv) {
	char *fname, *base_str;
	int max_length, buckets=0;
	if(argc < 3 || argc > 4) {
		printf("First input must be the base string, and second must be the txt file path.\n");
		printf("A third, optional input may be included to set the number of hash map buckets\n");
		return 0;
	}
	base_str=argv[1];
	fname=argv[2];
	max_length = strlen(base_str);
	if (argc==4) {
		buckets = atoi(argv[3]);   //if invalid numeric, buckets will be set to 0 and replace in next conditional
	} 
	if (buckets < 1) {
		buckets = (1 << (max_length+2))-1;
	}
	sortStr(base_str, max_length);

	power_set_map = hashMapCreate(buckets); 
	calculatePowerSet(base_str, max_length);

	processWordsFromFile(fname, max_length);

	hashMapDestroy(power_set_map);
	return 0;
}