
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
void processWordsFromFile(const char *fname, const int max_length)
 {
	FILE *input_file;                                 
	int char_count=0, word_count=0, formable_count=0, buff_index=0;
	int c;                                             //character returned from fgetc
	Table * temp_table = tableCreate(TABLE_SIZE);

	input_file= fopen(fname, "r");
	if(input_file==NULL) {                          //Prevents seg fault crash if there is a problem with the provided file
		printf("Improper file name: %s\n",fname);
		return;
	}

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
	fclose(input_file);
	reportResults(max_length,char_count, word_count, formable_count);
}

// main function which takes its inputs from the command line
int main (int argc, char **argv) {
	const char *fname;
	char *base_str;
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

	base_str_table = tableCreate(TABLE_SIZE);
	fillTable(base_str_table,base_str);

	power_set_map = hashMapCreate(buckets); 
	calculatePowerSet(base_str, max_length);
	processWordsFromFile(fname, max_length);

	tableDestroy(base_str_table);
	hashMapDestroy(power_set_map);
	return 0;
}