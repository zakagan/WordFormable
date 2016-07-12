//
// SinglyLinkedString.h
//

#ifndef SINGLYLINKEDSTRING_H
#define SINGLYLINKEDSTRING_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// A singularly linked list used for a stack structure
typedef struct node {
	char* S;
	int length, last_index;    //length is the length of the cstring S
	struct node* next;
} Node;

void push(Node **head_node, const char* cstring, const int cstring_length, const int last_index);
Node* pop(Node **head_node);

void destroyNode(Node *item);
void destroyStack(Node *stack);

int checkStackForString(const Node* n, const char* sorted_string, const int str_length);

#endif