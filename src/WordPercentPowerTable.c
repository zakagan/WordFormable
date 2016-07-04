
#include "WordPercentPowerTable.h"

// Generates the hash map from the base string, and updates the hash map's hash hit integers
void calculatePowerSet(const char* str, const int str_length) {
	int i;
	Node *item=NULL, *temp_stack = NULL;
	// this stack will be populated and used to replace the need for recursive calls
	Table* temp_table = tableCreate(TABLE_SIZE);
	for(i=0;i<str_length;i++) { 
		push(&temp_stack, temp_table, i);
		tableInsert(temp_stack->T,str[i]);
		//dispTable(temp_stack->T);
	}
	tableDestroy(temp_table);
	// The empty string is not added to the hash table because the routine will never have to look it up
	//printf("Calculating Power Set...\n");
	while(temp_stack!=NULL) {
		item=pop(&temp_stack);
		hashMapInsert(power_set_map, item);
		//dispTable(item->T);

		for(i=item->last_index; i<str_length-1; i++){                         //iterates last item through the size of the subset
			push(&temp_stack, item->T, i+1);
			tableInsert(temp_stack->T, str[i+1]);
		}
		destroyNode(item);
	}
	//printf("%s\n","Power Set calculation complete");
}

/* opens the provided txtfile, determines indvigual word tokens, and then calls a included method (checkWord) to see
if they are formable from the base string. Finally it prints the calculated result to the command line */
void processWordsFromFile(FILE* input_file, const int max_length)
 {                             
	int char_count=0, word_count=0, formable_count=0, buff_index=0;
	int c;                                             //character returned from fgetc
	Table * temp_table = tableCreate(TABLE_SIZE);

	do{
		c = fgetc(input_file);
		if(isTokenizer(c) || c==EOF) { 			
			if(buff_index>0){	                     //non-negative index + reaching a tokenizer means c_buff contains a token
				++word_count;
				char_count += buff_index;
				if(buff_index<=max_length && checkHashMapEntry(power_set_map, temp_table)) {	       
				  //token cannot formed by the base if it is larger than the base, if not the case consult hash map
					formable_count += isFormableTable(temp_table,base_str_table);    //if in hash map, confirm whether it is formable
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
	reportResults(max_length,char_count, word_count, formable_count);
}

void beginSolution(char* base_str, FILE* input_file, const int max_length, const int buckets) {

	base_str_table = tableCreate(TABLE_SIZE);
	fillTable(base_str_table,base_str);

	power_set_map = hashMapCreate(buckets); 
	calculatePowerSet(base_str, max_length);
	processWordsFromFile(input_file, max_length);

	tableDestroy(base_str_table);
	hashMapDestroy(power_set_map);
}