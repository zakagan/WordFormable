//
//  CharTable.h
//

#ifndef TABLESOLUTION_H
#define TABLESOLUTION_H

typedef struct {
    int size;            // size of the pointer table
    int *array;
} Table;

Table* tableCreate(int size);

void tableDestroy(Table* t);

unsigned char convertToUnsigned(const char c);

void fillTable(Table* t, const char *s);

void clearTable(Table* t, const char *s);

Table* copyTable(Table* destination, Table* source);

int compareTable(const Table* a, const Table* b);

void dispTable(const Table* t);



#endif