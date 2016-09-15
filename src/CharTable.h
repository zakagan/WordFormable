//
//  CharTable.h
//

#ifndef TABLESOLUTION_H
#define TABLESOLUTION_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct {
    unsigned int size;            // size of the pointer table
    unsigned int *array;
} Table;

Table* tableCreate(const unsigned int size);
void tableDestroy(Table* t);

void tableInsert(Table* t, const char key);
//void tableRemove(Table* t, const char key);

void fillTable(Table* t, const char *s);
//void removeWordTable(Table* t, const char *s);
void clearTable(Table* t);

unsigned int* generateIndex(const Table* source);
void indexDestroy(unsigned int* index);

Table* copyTable(Table* destination, const Table* source);
Table* copyTableFromIndex(Table* destination, const Table* source, const unsigned int* index);

//int compareTable(const Table* a, const Table* b);
int isFormableTable(const Table* a, const Table* b);
void dispTable(const Table* t);

#endif