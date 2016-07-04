//
//  WordPercentPowerTable.h
//

#ifndef WORDPERCENTPOWERTABLE_H
#define WORDPERCENTPOWERTABLE_H

#include "CharTable.h"
#include "SinglyLinkedTable.h"
#include "HashMapTable.h"
#include "Parsing.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Table* base_str_table;

HashMap* power_set_map; 

#define TABLE_SIZE 128   // Chosen based on the size of the standard ASCII character set

void beginSolution(char* base_str, FILE* input_file, const int max_length, const int buckets);

#endif