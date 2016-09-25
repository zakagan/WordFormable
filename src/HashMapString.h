//
// HashMapString.h
//

#ifndef HASHMAPSTRING_H
#define HASHMAPSTRING_H

#include <stdlib.h>
#include <stdio.h>
#include "SinglyLinkedList.h"
#include "CommunicativeHashFunction.h"

//A list of Nodes, indexed by hash values
typedef struct {
    size_t size;            // size of the pointer list
    Node **map;
} HashMap;

HashMap* hashMapCreate(size_t size);
void hashMapDestroy(HashMap* m);

unsigned char hashMapInsert(HashMap* m, Node* n);

Node* collectHashMapEntry(const HashMap* m, const char* cstring, const int str_length);


#endif