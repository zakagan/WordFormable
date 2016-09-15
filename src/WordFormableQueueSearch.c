#include "WordFormableQueueSearch.h"

/* Starting from the middle of a two directional queue, with ach node containing a pointer to a char from the sorted
 base string, search either forwards or backwards to see if the token's char has a match. Then dequeue that matching
  node and report that it has been found. If not report the word is unformable*/
int locateCharNode(Node** n, const char token_char) {
	Node* temp_node = NULL;
	if (*n) {
		if (token_char >= (*n)->char_ptr[0]) {
			//checking forward
			while (*n) {
				if (token_char == (*n)->char_ptr[0]) {
					// Match has been found, now determine where to step to next
					temp_node=*n;
					if ((*n)->next) {
						*n=(*n)->next; 				//first attempt to move forwards
					} else if ((*n)->prev) {
						*n=(*n)->prev; 			    // Occurs if at far end of queue
					} else{
						*n=NULL;                    // No more nodes remain
					}
					dequeue(temp_node);
					return 1;
				} else if (!(*n)->next || token_char < (*n)->char_ptr[0]) {
					break;							//further checking will not result in a match
				} else {
					*n = (*n)->next; 				//updates pointer for next check (forward)
				}
			}
		} else if (token_char < (*n)->char_ptr[0]) {
			//checking backward
			while (*n) {
				if (token_char == (*n)->char_ptr[0]) {
					temp_node=*n;
					if ((*n)->prev) {
						*n = (*n)->prev;			//first attempt to move backwards
					} else if ((*n)->next) {
						*n = (*n)->next;		    // Occurs when back at start of queue
					} else{
						*n=NULL;					// No more nodes remain
					}
					dequeue(temp_node);
					return 1;
				} else if (!(*n)->prev || token_char > (*n)->char_ptr[0]) {
					break;		//further checking will not result in a match
				} else {
					*n = (*n)->prev;				//updates pointer for next check (backward)
				}
			}
		}
	}
	return 0;
}
/* Opens the provided txtfile, and compares each letter with a two directional queue generated from
 the base string. The function keeps track of whether or not the word is formable. Then when a tokenizer
 is found the word counter updates, and so does the formable word counter, depernding on its status */
void processTokensFromFile(char* base_str, FILE* input_file, char* c_buff, char* copy_buff, const unsigned int max_length, const unsigned int silence, const size_t buckets)
 {  
	Node *current_node=NULL;
	Node** node_array;
	int char_count=0, word_count=0, formable_count=0, buff_index=0, is_formable=1, mid_index=max_length/2;
	int c;                                             //character returned from fgetc

	sortStr(base_str, max_length);
	node_array=buildListFromString(current_node, base_str, max_length);
	current_node=node_array[mid_index];

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
            resetLinksFromArray(node_array, max_length);
            current_node=node_array[mid_index];    
            memset(&c_buff[0],0,max_length);             
        }
        else
        {
            if(is_formable) { 
                if(locateCharNode(&current_node,c)) {  
                    c_buff[buff_index]=c; 
                } else {
                    is_formable=0;
                }    
            } 
            ++buff_index;
        }

    } while(c!=EOF);

	destroyDownQueue(node_array[0]);
	free(node_array);
	reportResults(max_length,char_count, word_count, formable_count);
}