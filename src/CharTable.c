#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "CharTable.h"

// Creates memory space for a table of character & their frequency values within a string
Table* tableCreate(int size)
{
    Table* t;

    t = malloc(sizeof(Table)); 
    assert(t != 0);
    t->size = size;
    t->array =  calloc(t->size,sizeof(int*));
    assert(t->array != 0);

    return t;
}

// Frees memory used for the character tables
void tableDestroy(Table* t)
{
    free(t->array);
    free(t);
}

// Trivial hash function for converting characters into unsigned number vals
unsigned char convertToUnsigned(const char c)
{
    unsigned const char acsii_val = c;
    return acsii_val;                             //Trivial since we give it only single chars
}


// inserts a new entry into the table structure
void tableInsert(Table* t, const char *key)
{
    unsigned char h;
    assert(key);
    h = convertToUnsigned(*key);
    if (t->array[h]!=0)
    {
    	t->array[h]++;
    }
    else 
    {	
	    t->array[h]=1;
    }
}

// removes a single entry from the table structure
void tableRemove(Table* t, const char *key)
{
    unsigned char h;
    assert(key);
    h = convertToUnsigned(*key);
    t->array[h]=0;

}

// Fills the tables structure with chars from the base string
void fillTable(Table* t, const char *s)
{
    const char *us;
    for(us = s; *us; us++) {
        tableInsert(t, us);
    }
}

// Clears the entire table structure
void clearTable(Table* t, const char *s)
{
    const char *us;
    for(us = s; *us; us++) {
        tableRemove(t, us);
    }
}

Table* copyTable(Table* destination, Table* source)
{
    if (destination->size != source->size) {
        return 0;
    } else {
        for (int i = 0; i < destination->size; ++i)
        {
            destination->array[i] = source->array[i];
        }
        return destination;
    }    
}

int compareTable(const Table* a, const Table* b) {
    if (a->size != b->size) {
        return 0;
    } else {
        for (int i = 0; i < a->size; ++i)
        {
            if (a->array[i] != b->array[i]) {
                return 0;
            }
        }
        return 1;
    }    
}


//  Prints the table to the commandline, used for lazy debugging
void dispTable(const Table* t) {
    int i;
    for(i=0; i<t->size; i++) {
        printf("%c: %d\n",(char) i, t->array[i]); 
    }
}

