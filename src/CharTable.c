
#include "CharTable.h"

// Creates memory space for a table of character & their frequency values within a string
Table* tableCreate(const unsigned int size)
{
    Table* t;

    t = malloc(sizeof(Table)); 
    if (t==NULL){
        printf("Memory allocation failed: table pointer t\n");
        exit(0);
    }
    t->size = size;
    t->array = calloc(t->size, sizeof(unsigned int));
    if (t->array==NULL){
        printf("Memory allocation failed: int pointer t->array\n");
        exit(0);
    }

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

/*
// removes a single entry from the table structure
void tableRemove(Table* t, const char key)
{
    unsigned char h;
    h = key;
    if (t->array[h]) {
        t->array[h]--;
    }
}
*/

// Fills the tables structure with chars from the base string
void fillTable(Table* t, const char *s)
{
    const char *us;
    for(us = s; *us; us++) {
        tableInsert(t, *us);
    }
}

/*
// removes one word from a table structure
void removeWordTable(Table* t, const char *s)
{
    const char *us;
    for(us = s; *us; us++) {
        tableRemove(t, *us);
    }
}
*/

// fully clears the table, leaving all entries equal to 0
void clearTable(Table* t)
{
    unsigned int i;            
    for(i = 0; i < t->size; i++) {
        t->array[i]=0;
    }
}

//Creates index that can be used to refill a table based on my index
unsigned int* generateIndex(const Table* source) {
    unsigned int i,j=0;
    unsigned int* index = calloc(source->size, sizeof(unsigned int));
    if (index==NULL){
        printf("Memory allocation failed: unsigned int pointer index\n");
        exit(0);
    }

    for (i = 0; i < source->size; ++i)
    {
        if (source->array[i]) {                 // if that bin in the table is nonempty, add it to the array of indexes
            index[j]=i;
            j++;
        }
    }
    return index;
}

//releases memory used for an index
void indexDestroy(unsigned int* index) {
    free(index);
}

// copies the array of one table, to another, given that the later has already been initialized
Table* copyTable(Table* destination, const Table* source)
{
    unsigned int i;
    if (destination->size != source->size) {
        return NULL;
    } else {
        for (i = 0; i < destination->size; i++)
        {
            destination->array[i] = source->array[i];
        }
        return destination;
    }    
}

// copies the array of one table, to another, based on a provided index, given that the later has already been initialized
Table* copyTableFromIndex(Table* destination, const Table* source, const unsigned int* index)
{
    unsigned int i=0;
    if (destination->size != source->size) {
        return NULL;
    } else {
        while (index[i])
        {
            destination->array[index[i]] = source->array[index[i]];
            i++;
        }
        return destination;
    }    
}

/*
// returns 1 if the two tables are the same, 0 otherwise
int compareTable(const Table* a, const Table* b) {
    unsigned int i;
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
*/

// returns 1 if the 1st table can be formed from the 2nd, 0 otherwise. 
int isFormableTable(const Table* a, const Table* b) {
    unsigned int i=0;
    if (a->size != b->size) {
        return 0;
    } else {
        for (i = 0; i < a->size; i++)
        {
            if (a->array[i] > b->array[i]) {
                return 0;
            }
        }
        return 1;
    }    
}


//  Prints the table to the commandline, used for lazy debugging
void dispTable(const Table* t) {
    unsigned int i, n;
    for(i=0; i<t->size; i++) {
        n = t->array[i];
        if(n) {
            printf("%c: %d\n",(char) i, n); 
        }
    }
}


