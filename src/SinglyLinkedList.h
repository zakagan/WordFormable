//
// SinglyLinkedList.h
//

#ifndef SINGLYLINKEDLIST_H
#define SINGLYLINKEDLIST_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "CharTable.h"

// A singularly linked list used for a stack structure
typedef struct node {
	Table* T;
	int length, last_index;    //length is the number of elements in the power set
	struct node* next;
} Node;

void push(Node **head_node, const Table* char_table, const int last_index);
Node* pop(Node **head_node);

void destroyStack(Node *stack);

#endif