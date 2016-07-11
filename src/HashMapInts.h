//
// HashMapInts.h
//

#ifndef HASHMAPINTS_H
#define HASHMAPINTS_H

#include <stdlib.h>
#include <stdio.h>
#include "CommunicativeHashFunction.h"

typedef struct {
    int size;            // size of the pointer list
    unsigned int *map;   // array listing the number of hash insertions to each entry
} HashMap;

HashMap* hashMapCreate(const size_t size);
void hashMapDestroy(HashMap* m);

void hashMapUpdate(HashMap* m, const char* str);

int checkValidityHashMap(const HashMap* m, const char* str);


#endif