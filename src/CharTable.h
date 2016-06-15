//
//  CharTable.h
//

#ifndef TABLESOLUTION_H
#define TABLESOLUTION_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

typedef struct {
    int size;            // size of the pointer table
    int *array;
} Table;

Table* tableCreate(int size);
void tableDestroy(Table* t);

void tableInsert(Table* t, const char key);
void tableRemove(Table* t, const char key);

void fillTable(Table* t, const char *s);
void removeWordTable(Table* t, const char *s);
void clearTable(Table* t);

Table* copyTable(Table* destination, const Table* source);

int compareTable(const Table* a, const Table* b);
int isFormableTable(const Table* a, const Table* b);
void dispTable(const Table* t);

#endif