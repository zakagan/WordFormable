//
//  WordFormablePowerString.h
//

#ifndef WORDFORMABLEPOWERSTRING_H
#define WORDFORMABLEPOWERSTRING_H

#include "CharTable.h"
#include "SinglyLinkedList.h"
#include "HashMapString.h"
#include "WordSort.h"
#include "Parsing.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void processTokensFromFile(char* base_str, FILE* input_file, char* c_buff, char* copy_buff, const unsigned int max_length, const unsigned int silence, const size_t buckets);

#endif