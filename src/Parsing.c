#include "Parsing.h"

// Checks if a single char is within a string of tokenizers 
unsigned char isTokenizer(const char a) {     
	if(strchr("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz-",a)) {
		return 0;
	} else {
		return 1;
	}
}

// Generates the first print out for non-silenced tests
void displayIntro(const unsigned int file_num, const char* file_name) 
{
	printf("Formable words within file #%u %s:\n",file_num,file_name);
}

// Generates the final print out on the command line
void reportResults(const unsigned int str_length, const unsigned int total_chars, const unsigned int total_words, const unsigned int total_formable_words)
{
	printf("%s","Base string length: ");
	printf("%d\n",str_length);
	printf("%s","Number of chars read from file: ");
	printf("%d\n",total_chars);
	printf("%s","Number of tokenized words read from file: ");
	printf("%d\n",total_words);
	printf("%s","Number of words formable from the base string: ");
	printf("%d\n",total_formable_words);
	printf("%s","Average word length in dictionary: ");
	printf("%.2f\n",(total_words > 0) ? (total_chars / (float) total_words) : 0.f);
	printf("%s","Percent of formable words: ");
	printf("%.2f\n",(total_words > 0) ? (total_formable_words / (float) total_words)*100 : 0.f);
}