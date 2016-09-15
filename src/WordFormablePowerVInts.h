//
//  WordFormablePowerVInts.h
//

#ifndef WORDFORMABLEPOWERVINTS_H
#define WORDFORMABLEPOWERVINTS_H

#include "CharTable.h"
#include "SinglyLinkedList.h"
#include "HashMapVInts.h"
#include "CheckWordByPartials.h"
#include "WordSort.h"
#include "Parsing.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void processTokensFromFile(char* base_str, FILE* input_file, char* c_buff, char* copy_buff, const unsigned int max_length, const int unsigned silence, const size_t buckets);

#endif