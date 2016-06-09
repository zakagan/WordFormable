#include "parsing.h"

// Checks if a single char is within a string of tokenizers 
int isTokenizer(const char a) {     
	if(strchr("\n \t,.!?\";:()<>{}[]\\/_@#$^&*+=|`~",a)) {
		return 1;
	} else {
		return 0;
	}
}

// Generates the final print out on the command line
void reportResults(int total_words, int total_formable_words) {
	printf("%s","Number of tokenized words read from file: ");
	printf("%d\n",total_words);
	printf("%s","Number of words formable from the base string: ");
	printf("%d\n",total_formable_words);
	printf("%s","Percent of formable words: ");
	printf("%.2f\n",(total_formable_words / (float) total_words)*100);
}
