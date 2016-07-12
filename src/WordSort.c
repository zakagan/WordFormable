#include "WordSort.h"


//inputted comparision used for qsort function, following immediately afterward
int comparFunc(const void *a, const void *b)
{
    return *(const char *)a - *(const char *)b;
}

//alphabetizies a given string using quick sort, in to order to facilitate searching
void sortStr(char *str, int str_length) 
{
	qsort(str, str_length, sizeof(char), comparFunc);
}
