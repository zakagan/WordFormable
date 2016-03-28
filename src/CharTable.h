//
//  CharTable.h
//

#ifndef CHARTABLE_H
#define CHARTABLE_H

typedef struct table *Table;

Table base_table;
char* base_str;

void dispTable(Table t);

// Saves the base string and builds a table that will be used to analyze tokens from the textfile
void setUpBase(char* str, int max_length);

// Cleans the data structures allocated in the heap before the routine terminates
void cleanUpBase();

/* Fills the table structures with chars from the base string, and then checks if a token can be formed by those chars by
consulting the table. Returns 1 if the word can be formed from the base string, 0 otherwise. Since values in the table
are decremented during look up, the table is cleared after completing a check */
int checkWord(char *str, int str_length);

#endif