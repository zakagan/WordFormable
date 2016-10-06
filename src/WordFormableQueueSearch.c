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
void processTokensFromFile(char** base_array, const char** fname_array, const unsigned int num_inputs, const unsigned int* length_array, \
 	const unsigned int max_length, const unsigned char silence, const unsigned char tare_setup, const size_t buckets)
 {  
	Node** node_array;
	Node *current_node=NULL;
	unsigned int char_count, word_count, formable_count, buff_index, mid_index;
	FILE *input_file;
	char *c_buff=NULL;
	int c;                                             //character returned from fgetc
	unsigned char is_formable;

	c_buff= calloc(max_length+1, sizeof(char));		//used to build word tokens as read from the provided file
	if (c_buff==NULL){
		printf("Memory allocation failed: char pointer c_buff\n");
		exit(0);
	}

	sortStr(base_array[0], length_array[0]);
	node_array=buildListFromString(current_node, base_array[0], length_array[0]);

	if (!tare_setup) {
		for(unsigned int i=0; i<num_inputs; ++i) {
			char_count=0, word_count=0, formable_count=0, buff_index=0, mid_index=length_array[0]/2;
			is_formable=1;
			current_node=node_array[mid_index];

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
						buff_index=0, is_formable=1;           
						resetLinksFromArray(node_array, length_array[0]);
						current_node=node_array[mid_index];    
						memset(&c_buff[0],0,(buff_index < max_length) ? buff_index : max_length);        
		            }
		            else {
						++char_count;		// A tokenizer char has been found, but no token is being formed
					}     
		        }
		        else {
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
			--char_count;		//correct for EOF being read for a char
			fclose(input_file);
			reportResults(length_array[0],char_count, word_count, formable_count);
		}
	}

	destroyDownQueue(node_array[0]);
	free(node_array);
	free(c_buff);
}