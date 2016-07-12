#include "SinglyLinkedString.h"

// creates a node for a singularly linked list and appends itself to the top of the stack 
void push(Node **head_node, const char* cstring, const int cstring_length, const int last_index) {
	Node* temp_node = malloc(sizeof(Node));
	if (temp_node==NULL){
		printf("Memory allocation failed: Node pointer temp_node\n");
		exit(0);
	}

	temp_node->S = calloc(sizeof(char), cstring_length + 1); // + 1 for final '\0' 
	if (temp_node->S==NULL){
		printf("Memory allocation failed: char pointer temp_node->S\n");
		exit(0);
	}
	strncpy(temp_node->S,cstring,cstring_length);

	temp_node->length = cstring_length;
	temp_node->last_index = last_index;
	temp_node->next = *head_node;               // Next is really the previously pushed node
	*head_node =temp_node;
} 

/* removes the top of the stack and returns it */
Node* pop(Node **head_node) {
		Node *temp_node = *head_node; // grab the current head
		*head_node = temp_node->next; // remove head from stack
		temp_node->next = 0;	
		return temp_node;	
}

// frees a single node
void destroyNode(Node *item) {
	free(item->S);
	free(item);	
}

// Frees memory usd back the singularly linked list
void destroyStack(Node *stack) {
	while(stack!=NULL) {
		destroyNode(pop(&stack));	
	}
}

// assuming a sorted string, searches for it within a stack of nodes. If found returns 1, 0 otheriwse.
int checkStackForString(const Node* n, const char* sorted_string, const int str_length) {
    while(n) {
        if (strncmp(sorted_string, n->S, str_length)!=0) {
            n = n->next;
        } else {
            return 1;
        }
    }
    return 0;
}