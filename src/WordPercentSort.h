//
//  WordPercentSort.h
//

#ifndef WORDPERCENTSORT_H
#define WORDPERCENTSORT_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>  
#include <assert.h>
#include "WordSort.h" 
#include "Parsing.h"

char *base_str, *partial_buff;     

void beginSolution(char* provided_base_str, FILE* input_file, const int max_length, const int buckets);         

#endif