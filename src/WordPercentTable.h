//
//  WordPercentTable.h
//

#ifndef WORDPERCENTTABLE_H
#define WORDPERCENTTABLE_H

#include "CharTable.h"
#include "Parsing.h"

Table *base_table, *comparison_table;
char *fname;
char *base_str;
#define TABLE_SIZE 128   // Chosen based on the size of the standard ASCII character set

#endif