
#include "WordPercentPowerSet.h"

void calculatePowerSet(char *str, int str_length) {
	int i;
	Node *item=NULL, *temp_stack = NULL;
	// this stack will be populated and used to replace the need for recursive calls
	Table* temp_table = tableCreate(TABLE_SIZE);
	//printf("%s\n", "Calculating Power Set...");
	//printf("%s\n", "Filling stack with single chars from base string");
	for(i=0;i<str_length;i++) { 
		push(&temp_stack, temp_table, i);
		tableInsert(temp_stack->T,str[i]);
		//dispTable(temp_stack->T);
	}
	tableDestroy(temp_table);
	// The empty string is not added to the hash table because the routine will never have to look it up
	while(temp_stack!=NULL) {
		item=pop(&temp_stack);
		hashMapInsert(power_set_map, item);
		//dispTable(item->T);

		for(i=item->last_index; i<str_length-1; i++){                         //iterates last item through the size of the subset
			push(&temp_stack, item->T, i+1);
			tableInsert(temp_stack->T, str[i+1]);
		}
		free(item->T);
		free(item);	
	}
	//printf("%s\n","Power Set calculation complete");
}

/* opens the provided txtfile, determines indvigual word tokens, and then calls a included method (checkWord) to see
if they are formable from the base string. Finally it prints the calculated result to the command line */
void processWordsFromFile()
 {
	FILE *input_file;                                  //used to construct token from read characters
	int word_count=0, formable_count=0, buff_index=0;
	int c;                                             //character returned from fgetc
	Table * temp_table = tableCreate(TABLE_SIZE);

	input_file= fopen(fname, "r");
	do{
		c = fgetc(input_file);
		if(isTokenizer(c) || c==EOF) { 			
			if(buff_index>0){	                     //non-negative index + reaching a tokenizer means c_buff contains a token
				++word_count;
				if(buff_index<=max_length) {	         //token cannot formed by the base if it is larger than the base
					formable_count+=checkHashMapForTable(power_set_map, temp_table);
				}		
			}
			buff_index=0;			
			clearTable(temp_table);        //resets temp_table so it can be reused to build the next token
		}
		else
		{
			if(buff_index<max_length) {	
				tableInsert(temp_table, c);             //appends the current char to partial token 
			}
			++buff_index;
		}

	} while(c!=EOF);

	tableDestroy(temp_table);
	fclose(input_file);
	reportResults(word_count, formable_count);
}

// main function which takes its inputs from the command line
int main (int argc, char **argv) {
	if(argc !=3) {
		printf("%s\n", "first input must be the base string, and second must be the txt file path");
		return 0;
	}
	char* base_str;
	base_str=argv[1];
	fname=argv[2];
	max_length = strlen(base_str);
	power_set_map = hashMapCreate((1 << (max_length+1)));
	calculatePowerSet(base_str, max_length);
	processWordsFromFile();

	hashMapDestroy(power_set_map);
	return 0;
}