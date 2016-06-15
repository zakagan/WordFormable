//
// HashMapString.h
//

#ifndef HASHMAPSTRING_H
#define HASHMAPSTRING_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "SinglyLinkedString.h"

//A list of Nodes, indexed by hash values
typedef struct {
    int size;            // size of the pointer list
    Node **map;
} HashMap;

HashMap* hashMapCreate(size_t size);
void hashMapDestroy(HashMap* m);

int hashMapInsert(HashMap* m, Node* n);

Node* collectHashMapEntry(const HashMap* m, const char* cstring, const int str_length);


#endif