//
// PowerSetString.h
//

#ifndef POWERSETSTRING_H
#define POWERSETSTRING_H

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>
#include "WordSort.h"
#include "Parsing.h"

// A singularly linked list used for a stack structure
typedef struct node {
	char* S;
	int length, last_index;    //length is the number of elements in the power set
	struct node* next;
} Node;

//A list of Nodes, indexed by hash values
typedef struct {
    int size;            // size of the pointer table
    Node **map;
} HashMap;

Node *saved_stack;

HashMap* saved_map; //hash map made from our inputted file


#endif