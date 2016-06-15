#include "SinglyLinkedTable.h"

/* creates a node for a singularly linked list and appends itself to the top of the stack */
void push(Node **head_node, const Table* char_table, const int last_index) {
	Node* temp_node = malloc(sizeof(Node));
	assert(temp_node != 0);

	temp_node->T = tableCreate(char_table->size);
	copyTable(temp_node->T, char_table);

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
	tableDestroy(item->T);
	free(item);	
}

// Frees memory usd back the singularly linked list
void destroyStack(Node *stack) {
	while(stack!=NULL) {
		destroyNode(pop(&stack));	
	}
}