//
//  WordFormablePartials.h
//

#ifndef WORDFORMABLEPARTIALS_H
#define WORDFORMABLEPARTIALS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>  
#include "WordSort.h" 
#include "CheckWordByPartials.h"
#include "Parsing.h"

void processTokensFromFile(char* base_str, FILE* input_file, char* c_buff, char* copy_buff, const unsigned int max_length, const unsigned char silence, const unsigned char tare_setup,  const size_t buckets);

#endif