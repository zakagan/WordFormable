//
//  WordFormableTable.h
//

#ifndef WORDFORMABLETABLE_H
#define WORDFORMABLETABLE_H

#include "CharTable.h"
#include "Parsing.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define TABLE_SIZE 128   // Chosen based on the size of the standard ASCII character set

void processTokensFromFile(char* base_str, FILE* input_file, char* c_buff, char* copy_buff, const unsigned int max_length, const unsigned char silence, const unsigned char tare_setup,  const size_t buckets);

#endif