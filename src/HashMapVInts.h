//
// HashMapVInts.h
//

#ifndef HASHMAPVINTS_H
#define HASHMAPVINTS_H

#include <stdlib.h>
#include <stdio.h>
#include "CommunicativeHashFunction.h"

typedef struct {
    int size;            // size of the pointer list
    unsigned short *map;   // array listing the number of hash insertions to each entry
} HashMap;

HashMap* hashMapCreate(const size_t size);
void hashMapDestroy(HashMap* m);

void hashMapUpdate(HashMap* m, const char* str);

unsigned char checkValidityHashMap(const HashMap* m, const char* str);


#endif