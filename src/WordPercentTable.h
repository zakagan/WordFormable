//
//  WordPercentTable.h
//

#ifndef WORDPERCENTTABLE_H
#define WORDPERCENTTABLE_H

#include "CharTable.h"
#include "Parsing.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Table *base_table, *comparison_table;
#define TABLE_SIZE 128   // Chosen based on the size of the standard ASCII character set

void beginSolution(char* base_str, FILE* input_file, const int max_length, const int buckets);   

#endif