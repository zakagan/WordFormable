//
//  WordPercentSort.h
//

#ifndef WORDPERCENTSORT_H
#define WORDPERCENTSORT_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>  
#include "WordSort.h" 
#include "CheckWordByPartials.h"
#include "Parsing.h"

void processTokensFromFile(char* base_str, FILE* input_file, char* c_buff, const int max_length, const int silence, const int buckets);

#endif