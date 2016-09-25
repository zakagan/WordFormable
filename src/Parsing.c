#include "Parsing.h"

// Checks if a single char is within a string of tokenizers 
unsigned char isTokenizer(const char a) {     
	if(strchr("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz-",a)) {
		return 0;
	} else {
		return 1;
	}
}

// Generates the final print out on the command line
void reportResults(int str_length, int total_chars, int total_words, int total_formable_words) {
	printf("%s","Base string length: ");
	printf("%d\n",str_length);
	printf("%s","Number of chars read from file: ");
	printf("%d\n",total_chars);
	printf("%s","Number of tokenized words read from file: ");
	printf("%d\n",total_words);
	printf("%s","Number of words formable from the base string: ");
	printf("%d\n",total_formable_words);
	printf("%s","Average word length: ");
	printf("%.2f\n",(total_chars / (float) total_words));
	printf("%s","Percent of formable words: ");
	printf("%.2f%%\n",(total_formable_words / (float) total_words)*100);
}