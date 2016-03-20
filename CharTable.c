#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>

#include "CharTable.h"

#define TABLE_SIZE 128

struct table {
    int size;           /* size of the pointer table */
    int *array;
};

Table tableCreate()
{
    Table t;
    int i;

    t = malloc(sizeof(*t));
    assert(t != 0);

    t->size = TABLE_SIZE;
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

unsigned char hashFunc(const char *letter)		//Trivial since we give it only single chars
{
    return (unsigned const char) *letter;
}


/* insert a new entry into the array */
void tableInsert(Table t, const char *key)
{
    unsigned char h;
    assert(key);
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

void tableRemove(Table t, const char *key)
{
    unsigned char h;
    assert(key);
    h = hashFunc(key);
    t->array[h]=0;

}

void fillTable(const char *s, Table t)
{
    const char *us;
    for(us = s; *us; us++) {
        tableInsert(t, us);
    }
}

void clearTable(const char *s, Table t)
{
    const char *us;
    for(us = s; *us; us++) {
        tableRemove(t, us);
    }
}

int searchTable(const char *s, Table t)
{
    const unsigned char *us;

    for(us = (const unsigned char *) s; *us; us++) {
        if (t->array[*us]>0) {
            t->array[*us]--;
        }
        else 
        {
            return 0;
        }
    }    
    return 1;
}

void dispTable(Table t) {
    int i;
    for(i=0; i<t->size; i++) {
        printf("%c: %d\n",(char) i, t->array[i]); 
    }
}

