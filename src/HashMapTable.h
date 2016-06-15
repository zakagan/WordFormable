//
// HashMapTable.h
//

#ifndef HASHMAPTABLE_H
#define HASHMAPTABLE_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "CharTable.h"
#include "SinglyLinkedTable.h"

//A list of Nodes, indexed by hash values
typedef struct {
    int size;            // size of the pointer list
    unsigned short *map;            // array listing the number of hash insertions to each entry
} HashMap;

HashMap* hashMapCreate(const size_t size);
void hashMapDestroy(HashMap* m);

void hashMapInsert(HashMap* m, Node* n);

int checkHashMapEntry(const HashMap* m, const Table* char_table);


#endif