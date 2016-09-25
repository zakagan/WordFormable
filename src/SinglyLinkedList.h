//
// SinglyLinkedString.h
//

#ifndef SINGLYLINKEDLIST_H
#define SINGLYLINKEDLIST_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// A singularly linked list used for a stack structure
typedef struct node {
	char* S;
	int length, last_index;    //length is the length of the cstring S, last-length is the index of the last added base string char
	struct node* prev;
} Node;

void push(Node **head_node, const char* cstring, const unsigned int cstring_length, const unsigned int last_index);
Node* pop(Node **head_node);

void destroyNode(Node *item);
void destroyStack(Node *stack);

unsigned char checkStackForString(const Node* n, const char* sorted_string, const unsigned int str_length);

#endif