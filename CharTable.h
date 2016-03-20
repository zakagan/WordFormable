//
//  CharTable.h
//

#ifndef CHARTABLE_H
#define CHARTABLE_H

typedef struct table *Table;

Table tableCreate();

void tableDestroy(Table);

unsigned char hashFunc(const char *s);

void fillTable(const char *s, Table t);

void clearTable(const char *s, Table t);

int searchTable(const char *s, Table t);

void dispTable(Table t);

#endif