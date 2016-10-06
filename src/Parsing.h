//
//  Parsing.h
//

#ifndef PARSING_H
#define PARSING_H

#include <stdlib.h>  
#include <stdio.h>
#include <string.h>

unsigned char isTokenizer(const char a);
void displayIntro(const unsigned int file_num, const char* file_name);
void reportResults(const unsigned int str_length, const unsigned int total_chars, const unsigned int total_words, const unsigned int total_formable_words);

#endif