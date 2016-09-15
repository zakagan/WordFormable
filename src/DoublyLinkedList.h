//
// DoublyLinkedList.h
//

#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

#include <stdlib.h>
#include <stdio.h>

// A doubly linked list used to implement a two directional queue
typedef struct node {
	const char* char_ptr;
	struct node* prev;
	struct node* next;
} Node;

Node* enqueue(Node *selected_node, const char* char_ptr) ;
void dequeue(Node *selected_node);

void destroyDownQueue(Node *queue);

Node** buildListFromString(Node* head_node, const char* base_str, const unsigned int max_length);

void resetLinksFromArray(Node** node_array, const unsigned int max_length);

#endif