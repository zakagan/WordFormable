#include "WordFormableBinarySearch.h"

int checkDownwards(Node** node_array, const char token_char, unsigned int end, unsigned int index) {
	Node* current_node=node_array[++index];
	while (index <= end && current_node->char_ptr[0]==token_char) {
		if (current_node->valid_flag) {
			current_node->valid_flag=0;
			return 1;
		}
		current_node=node_array[++index];
	}
	return 0;
}

int checkUpwards(Node** node_array, const char token_char, unsigned int start, unsigned int index) {
	Node* current_node=node_array[--index];
	while (index >= start && current_node->char_ptr[0]==token_char) {
		if (current_node->valid_flag) {
			current_node->valid_flag=0;
			return 1;
		}
		current_node=node_array[--index];
	}
	return 0;
}

/* */
int BinarySearch(Node** node_array, const char token_char, unsigned int start, unsigned int end) {
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
		else if (checkUpwards(node_array, token_char, start, mid)) {
			return 1;
		}
		else {
			return checkDownwards(node_array, token_char, end, mid);
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
void processTokensFromFile(char* base_str, FILE* input_file, char* c_buff, char* copy_buff, const unsigned int max_length, const unsigned int silence, const size_t buckets)
 {  
	Node** node_array;
	int char_count=0, word_count=0, formable_count=0, buff_index=0, is_formable=1;
	int c;                                             //character returned from fgetc

	sortStr(base_str, max_length);
	node_array=buildListFromString(base_str, max_length);

    do{
        c = fgetc(input_file);                       //gets next character
        if(isTokenizer(c) || c==EOF) {          
            if(buff_index>0){                        //non-negative index + reaching a tokenizer means c_buff contains a token
                ++word_count;
                char_count += buff_index;
                if(is_formable) {            
                    ++formable_count;
                    if (!silence) {printf("\t%s\n",c_buff);}
                }       
            }
            //reset params for next loop and next token
            buff_index=0, is_formable=1;           
            resetValidity(node_array, max_length);   
            memset(&c_buff[0],0,max_length);             
        }
        else
        {
            if(is_formable) { 
                if(BinarySearch(node_array, c, 0, max_length-1)) {  
                    c_buff[buff_index]=c; 
                } else {
                    is_formable=0;
                }    
            } 
            ++buff_index;
        }

    } while(c!=EOF);

	destroyByArray(node_array, max_length);
	free(node_array);
	reportResults(max_length,char_count, word_count, formable_count);
}