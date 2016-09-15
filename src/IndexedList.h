//
// IndexedList.h
//

#ifndef INDEXEDLIST_H
#define INDEXEDLIST_H

#include <stdlib.h>
#include <stdio.h>

// A doubly linked list used to implement a two directional queue
typedef struct node {
	const char* char_ptr;
	int valid_flag;
} Node;

Node** buildListFromString(const char* base_str, const unsigned int max_length);

void destroyByArray(Node **node_array, const unsigned int max_length);

void resetValidity(Node** node_array, const unsigned int max_length);

#endif