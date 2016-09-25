//
//  WordFormableBinarySearch.h
//

#ifndef WORDFORMABLEQUEUE_H
#define WORDFORMABLEQUEUE_H

#include "IndexedList.h"
#include "WordSort.h"
#include "Parsing.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void processTokensFromFile(char* base_str, FILE* input_file, char* c_buff, char* copy_buff, const unsigned int max_length, const unsigned char silence, const unsigned char tare_setup,  const size_t buckets);

#endif