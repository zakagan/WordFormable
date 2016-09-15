#include "IndexedList.h"

// Creates a doubly linkd list, with each node containing a pointer to a char from the string
Node** buildListFromString(const char* base_str, const unsigned int max_length) {
	Node** node_array = malloc(max_length * sizeof(Node*));  //This is what is returned, used to reset the queue's connections
	for (unsigned int i = 0; i < max_length; ++i)
	{
		node_array[i]=malloc(sizeof(Node));
		if (node_array[i]==NULL){
			printf("Memory allocation failed: Node pointer, as part of node_array\n");
			exit(0);
		}
		node_array[i]->char_ptr=&base_str[i];
		node_array[i]->valid_flag=1;
	}
	return node_array;
}

// Frees memory of all next nodes on the doubly linked list
void destroyByArray(Node **node_array, const unsigned int max_length) {
	for (unsigned int i=0; i <max_length; ++i) {
		free(node_array[i]);
	}
}

// reset th connections of the doubly linked list so that it matches the queue that was originally generated.
void resetValidity(Node** node_array, const unsigned int max_length) {
	for (unsigned int i = 0; i < max_length; ++i)
	{
		node_array[i]->valid_flag = 1;
	}
}