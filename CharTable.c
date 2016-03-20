#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>

#include "CharTable.h"

struct table {
    int size;           /* size of the pointer table */
    int length;              /* number of elements stored */
    int *array;
};

Table tableCreate(int size)
{
    Table t;
    int i;

    t = malloc(sizeof(*t));
    assert(t != 0);

    t->size = size;
    t->length = 0;
    t->array = malloc(sizeof(int*) * t->size);
    assert(t->array != 0);

    for(i = 0; i < t->size; i++) t->array[i] = 0;

    return t;
}

void tableDestroy(Table t)
{
    free(t->array);
    free(t);
}

int getLength(Table t)
{
    return t->length;
}

unsigned char hashFunc(const char *letter)		//Trivial since we give it only single chars
{
    return (unsigned const char) *letter;
}


/* insert a new entry into the array */
void tableInsert(Table t, const char *key)
{
    unsigned char h;
    assert(key);
    t->length++;
    h = hashFunc(key);
    if (t->array[h]!=0)
    {
    	t->array[h]++;
    }
    else 
    {	
	    t->array[h]=1;
    }
}

Table makeTable(const char *s)
{
    Table t=tableCreate(128);
    const char *us;
    for(us = s; *us; us++) {
        tableInsert(t, us);
    }
    return t;
}

int compareTables(Table alpha, Table beta)
{
    int i;
    for(i=0; i<128; i++) {
        if (alpha->array[i] < beta->array[i])
        {
            return 0;
        }
    }
    return 1;
}

void dispTable(Table t) {
    int i;
    for(i=0; i<128; i++) {
        printf("%c: %d\n",(char) i, t->array[i]); 
    }
}

