#include "DoublyLinkedList.h"

// creates a node for a doubly linked list and appends itself into the queue behind the selected node
Node* enqueue(Node *selected_node, const char* char_ptr) {
	Node* new_node = malloc(sizeof(Node));
	if (new_node==NULL){
		printf("Memory allocation failed: Node pointer new_node\n");
		exit(0);
	}
	new_node->char_ptr=char_ptr;

	new_node->prev = selected_node;               //it's okay if it's NULL
	if (selected_node) {
		new_node->next = selected_node->next;     //it's (also) okay if it's NULL
		if (selected_node->next) {
			selected_node->next->prev = new_node;
		} 
		selected_node->next= new_node; 			  // set its next node to the new node
	} else {
		new_node->next = NULL;
	}
	return new_node;
} 

/* removes the selcted node and attempts to connect the previous and next nodes to maintain the rest of the queue*/
void dequeue(Node *selected_node) {
	if (selected_node) {
		if (selected_node->prev) {
			selected_node->prev->next = selected_node->next;
		}
		if (selected_node->next) {
			selected_node->next->prev = selected_node->prev;
		}
	}
}

// Frees memory of all next nodes on the doubly linked list
void destroyDownQueue(Node *queue) {
	Node* temp_node=NULL;
	while(queue!=NULL) {
		temp_node=queue->next;
		free(queue);
		queue=temp_node;	
	}
}

// Creates a doubly linked list, with each node containing a pointer to a char from the string
Node** buildListFromString(Node* head_node, const char* base_str, const unsigned int max_length) {
	Node* tail_node=head_node;
	Node** node_array = malloc(max_length * sizeof(Node*));  //This is what is returned, used to reset the queue's connections
	for (unsigned int i = 0; i < max_length; ++i)
	{
		node_array[i]=enqueue(tail_node,&base_str[i]);
		tail_node=node_array[i];
	}
	return node_array;
}

// reset th connections of the doubly linked list so that it matches the queue that was originally generated.
void resetLinksFromArray(Node** node_array, const unsigned int max_length) {
	for (unsigned int i = 0; i < max_length; ++i)
	{
		node_array[i]->prev = (i > 0) ? node_array[i-1] : NULL;
		node_array[i]->next = (i < max_length-1) ? node_array[i+1] : NULL;
	}
}