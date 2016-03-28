//
//  SortWord.h
//

#ifndef SORTWORD_H
#define SORTWORD_H

char* base_str;

// Saves base string and alphabetizes it to set up a base for comparisions
void setUpBase(char* str, int max_length);

// Trivial here since nothing is saved to the heap.
void cleanUpBase();

/* Takes an alhabetized word and an alphabetized base string
returns 1 if the word can be formed from the base string, 0 otherwise */
int checkWord(char *str, int str_length);

#endif