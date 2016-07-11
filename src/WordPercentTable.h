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

#define TABLE_SIZE 128   // Chosen based on the size of the standard ASCII character set

void processTokensFromFile(char* base_str, FILE* input_file, char* c_buff, const int max_length, const int silence, const int buckets);

#endif