//
//  CharTable.h
//

#ifndef CHARTABLE_H
#define CHARTABLE_H

typedef struct table *Table;

Table tableCreate(int);

void tableDestroy(Table);

int getLength(Table t);

unsigned char hashFunc(const char *s);

void tableInsert(Table, const char *key);

Table makeTable(const char *s);

int compareTables(Table alpha, Table beta);

void dispTable(Table t);

#endif