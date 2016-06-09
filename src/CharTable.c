
#include "CharTable.h"

// Creates memory space for a table of character & their frequency values within a string
Table* tableCreate(int size)
{
    Table* t;

    t = malloc(sizeof(Table)); 
    assert(t != 0);
    t->size = size;
    t->array = calloc(t->size,sizeof(int*));
    assert(t->array != 0);

    return t;
}

// Frees memory used for the character tables
void tableDestroy(Table* t)
{
    free(t->array);
    free(t);
}

// inserts a new entry into the table structure
void tableInsert(Table* t, const char key)
{
    unsigned char h;
    h = key;          // index table by ascii value
    t->array[h]++; 
}

// removes a single entry from the table structure
void tableRemove(Table* t, const char key)
{
    unsigned char h;
    h = key;
    t->array[h]--;

}

// Fills the tables structure with chars from the base string
void fillTable(Table* t, const char *s)
{
    const char *us;
    for(us = s; *us; us++) {
        tableInsert(t, *us);
    }
}

// removes one word from a table structure
void removeWordTable(Table* t, const char *s)
{
    const char *us;
    for(us = s; *us; us++) {
        tableRemove(t, *us);
    }
}

// fully clears the table, leaving all entries equal to 0
void clearTable(Table* t)
{
    int i;            
    for(i = 0; i < t->size; i++) {
        t->array[i]=0;
    }
}

// copies the array of one table, to another, given that the later has already been initialized
Table* copyTable(Table* destination, const Table* source)
{
    int i;
    if (destination->size != source->size) {
        return 0;
    } else {
        for (i = 0; i < destination->size; ++i)
        {
            destination->array[i] = source->array[i];
        }
        return destination;
    }    
}
// returns 1 if the two tables are the same, 0 otherwise
int compareTable(const Table* a, const Table* b) {
    int i;
    if (a->size != b->size) {
        return 0;
    } else {
        for (i = 0; i < a->size; ++i)
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
    int i, n;
    for(i=0; i<t->size; i++) {
        n = t->array[i];
        if(n) {
            printf("%c: %d\n",(char) i, n); 
        }
    }
}

// returns 1 if the 1st table can be formed from the 2nd, 0 otherwise
/*
int isFormableTable(const Table* a, const Table* b) {
    int i;
    if (a->size != b->size) {
        return 0;
    } else {
        for (i = 0; i < a->size; ++i)
        {
            if (a->array[i] > b->array[i]) {
                return 0;
            }
        }
        return 1;
    }    
}
*/
