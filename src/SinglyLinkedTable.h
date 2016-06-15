//
// SinglyLinkedTable.h
//

#ifndef SINGLYLINKEDTABLE_H
#define SINGLYLINKEDTABLE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "CharTable.h"

// A singularly linked list used for a stack structure
typedef struct node {
	Table* T;
	int last_index; 
	struct node* next;
} Node;

void push(Node **head_node, const Table* char_table, const int last_index);
Node* pop(Node **head_node);

void destroyNode(Node *item) ;
void destroyStack(Node *stack);

#endif