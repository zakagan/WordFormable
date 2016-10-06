#include "WordFormableBinarySearch.h"

/* looks for un-used matching char nodes in those neighboriing the provided index, until it hits a non-mathcing node */
unsigned char check4Unused(Node** node_array, const char token_char, unsigned int start, unsigned int end, unsigned int index) {
	Node* current_node;
	unsigned char check_down=1, check_up=1;
	unsigned int index_up=index, index_down=index;
	while(check_down || check_up) {
		if(check_down) {
			current_node=node_array[++index_down];
			if(index_down<=end && current_node->char_ptr[0]==token_char) {
				if (current_node->valid_flag) {
					current_node->valid_flag=0;
					return 1;
				}
			}
			else {check_down=0;}
		}
		if (check_up) {
			current_node=node_array[--index_up];
			if(index_up>=start && current_node->char_ptr[0]==token_char) {
				if (current_node->valid_flag) {
					current_node->valid_flag=0;
					return 1;
				}
			} 
			else {check_up=0;}
		}
	}
	return 0;
}

/* Searches across the array of nodes for the character in question, dividing area of search by 2 each time. Once a matching char node is
  found, it either will be marked as used or if already used the above 2 functions will check for non-used, matching neighbor chars. */
unsigned char BinarySearch(Node** node_array, const char token_char, unsigned int start, unsigned int end) {
	unsigned int mid;
	Node* current_node;
	if (start > end) {return 0;}
	mid=(start+end)/2;
	current_node=node_array[mid];
	if (current_node->char_ptr[0]==token_char) {
		if (current_node->valid_flag) {							// means the char in this node has not been used before while checking this token
			current_node->valid_flag=0;
			return 1;
		}
		// Otherwise the surrounding nodes must be checked for additional matching chars
		else {
			return check4Unused(node_array, token_char, start, end, mid);
		}
	}
	else if (current_node->char_ptr[0] < token_char) {
		return BinarySearch(node_array, token_char, mid+1, end);
	}
	else if (mid !=0) {												// this check prevents unsigned overflow
		return BinarySearch(node_array, token_char, start, mid-1);
	}
	else {return 0;}
}

/* Opens the provided txtfile, and compares each letter with a two directional queue generated from
 the base string. The function keeps track of whether or not the word is formable. Then when a tokenizer
 is found the word counter updates, and so does the formable word counter, depernding on its status */
void processTokensFromFile(char** base_array, const char** fname_array, const unsigned int num_inputs, const unsigned int* length_array, \
 	const unsigned int max_length, const unsigned char silence, const unsigned char tare_setup, const size_t buckets)
 {  
	Node** node_array;
	unsigned int char_count, word_count, formable_count, buff_index,end_index;
	FILE *input_file;
	char *c_buff=NULL;
	int c;                                   //character returned from fgetc
	unsigned char is_formable;

	c_buff= calloc(max_length+1, sizeof(char));		//used to build word tokens as read from the provided file
	if (c_buff==NULL){
		printf("Memory allocation failed: char pointer c_buff\n");
		exit(0);
	}

	sortStr(base_array[0], length_array[0]);
	node_array=buildListFromString(base_array[0], length_array[0]);
	end_index=length_array[0]-1;

	if (!tare_setup) {
		for(unsigned int i=0; i<num_inputs; ++i) {
			char_count=0, word_count=0, formable_count=0, buff_index=0;
			is_formable=1;

			input_file= fopen(fname_array[i], "r");                 
			if(input_file==NULL) {                          //Prevents seg fault crash if there is a problem with the provided file
				printf("Improper file name: %s\n",fname_array[i]);
				continue;
			}

			if(!silence) {
				displayIntro(i+1,fname_array[i]);
			}

		    do{
		        c = fgetc(input_file);                       //gets next character
		        if(isTokenizer(c) || c==EOF) {          
		            if(buff_index>0){                        //non-negative index + reaching a tokenizer means c_buff contains a token
		                ++word_count;
						char_count += buff_index+1;			// +1 to account for the tokenizing character causing termination of token reading
		                if(is_formable) {            
		                    ++formable_count;
		                    if (!silence) {printf("\t%s\n",c_buff);}
		                }
		                //reset params for next loop and next token        
						resetValidity(node_array, length_array[0]);  
						memset(&c_buff[0],0,(buff_index < max_length) ? buff_index : max_length);
						buff_index=0, is_formable=1;       
		            }
					else {
						++char_count;		// A tokenizer char has been found, but no token is being formed
					}
		        }
		        else
		        {
		            if(is_formable) { 
		                if(BinarySearch(node_array, c, 0, end_index)) {  
		                    c_buff[buff_index]=c; 
		                } else {
		                    is_formable=0;
		                }    
		            } 
		            ++buff_index;
		        }

		    } while(c!=EOF);
			--char_count;		//correct for EOF being read for a char
			fclose(input_file);
			reportResults(length_array[0],char_count, word_count, formable_count);
		}
	}

	destroyByArray(node_array, length_array[0]);
	free(node_array);
	free(c_buff);
}