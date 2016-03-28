#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "CharTable.h"

#define TABLE_SIZE 128   // Chosen based on the size of the standard ASCII character set

struct table {
    int size;            // size of the pointer table
    int *array;
};


// Creates memory space for a table of character & their frequency values within the base string
Table tableCreate(size_t size)
{
    Table t;
    int i;

    t = (Table) malloc(sizeof(*t));
    assert(t != 0);

    t->size = size;
    t->array = (int*) malloc(sizeof(int*) * t->size);
    assert(t->array != 0);

    for(i = 0; i < t->size; i++) t->array[i] = 0;

    return t;
}

// Frees memory used for the character tables
void tableDestroy(Table t)
{
    free(t->array);
    free(t);
}

// Trivial hash function for processing characters in base string
unsigned char hashFunc(const char *c)		
{
    unsigned const char acsii_val = *c;
    assert(acsii_val > 0 && acsii_val < 128);
    return acsii_val;                             //Trivial since we give it only single chars
}


// inserts a new entry into the table structure
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

// removes a single entry from the table structure
void tableRemove(Table t, const char *key)
{
    unsigned char h;
    assert(key);
    h = hashFunc(key);
    t->array[h]=0;

}

// Fills the tables structure with chars from the base string
void fillTable(const char *s, Table t)
{
    const char *us;
    for(us = s; *us; us++) {
        tableInsert(t, us);
    }
}

// Clears the table structure so it can be refilled on the next pass
void clearTable(const char *s, Table t)
{
    const char *us;
    for(us = s; *us; us++) {
        tableRemove(t, us);
    }
}

/* Functions after this point are included in the header, for use in core file */

//  Prints the table to the commandline, used for lazy debugging
void dispTable(Table t) {
    int i;
    for(i=0; i<t->size; i++) {
        printf("%c: %d\n",(char) i, t->array[i]); 
    }
}

void setUpBase(char *str, int max_length) {
   // max_length is not used in this implementation 
    base_str=str;
    base_table=tableCreate(TABLE_SIZE);

}

void cleanUpBase() {
    tableDestroy(base_table);

}

int checkWord(char *str, int str_length)
{
    // str_length is not used in this implementation
    fillTable(base_str, base_table);
    const unsigned char *us;
    int return_val=1;
    for(us = (unsigned char *) str; *us; us++) {
        if (base_table->array[*us]>0) {
            base_table->array[*us]--;
        }
        else 
        {
            return_val=0;
        }
    }    
    clearTable(base_str, base_table);
    return return_val;
}
