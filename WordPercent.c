#include <stdio.h>
#include <string.h>
#include <stdlib.h>  

//Checks if a single char is within a string of tokenizers 
bool isTokenizer(char a) {     
	if(strchr(" ,.!?()<>{}[]\\/",a)) {
		return true;
	} else {
		return false;
	}
}

//inputted comparision used for qsort function immediately below
int comparFunc(const void *a, const void *b)
{
    return *(const char *)a - *(const char *)b;
}

//alphabetizies a given string, used to order strings to aid searching
void sortStr(char *str, int str_length) 
{
	qsort(str, str_length, sizeof(char), comparFunc);
}

//Takes an alhabetized word and an alphabetized basis string
//returns 1 if the word can be formed from the basis string, 0 otherwise
int checkWord(char *sorted_word, int str_length, char *sorted_basis) 
{	
	char cur_char, next_char;
	char *partial_word;                              //formed by concatinating all instances of a single char
	int word_index=0, partial_index, return_val=1;	
	partial_word= (char*) malloc(str_length);
	do{	
		partial_index=0;
		do{	
			cur_char= sorted_word[word_index];
			next_char= sorted_word[word_index+1];		
			partial_word[partial_index]=cur_char;    //adds each repeated char to partial_word
			++partial_index;
			++word_index;
		} while(cur_char==next_char);            
		if(strstr(sorted_basis, partial_word)==0)    //checks if all instances of this char can be found within the basis
		{
			return_val= 0;                           //result if partial_word could not be found in the basis
			memset(&partial_word[0],0,str_length);  
			break;
		} else {
			memset(&partial_word[0],0,str_length);  //resets partial_word so it can collect the instances of the next char
		}
	} while(next_char!='\0');
	free(partial_word);
	return return_val;
}

//opens the provided txtfile and counts the number of words within
//that can be made from characters in the basis string.
void processWordsFromFile(char *fname, char *basis_str)
 {
	FILE *input_file;
	input_file= fopen(fname, "r");

	bool started_word=false;	                     //used to track the parsing of text into individual tokens
	int c;                                           //character returned from fgetc
	char *c_buff;                                    //used to construct token from read characters
	int buff_index=0, word_count=0, formable_count=0;
	int max_length = (int) strlen(basis_str);		
	c_buff= (char*) malloc(max_length);	
	do{
		c = fgetc(input_file);
		if(isTokenizer(c) || c==EOF) { 
			if(started_word==true) {
				++word_count;		
				sortStr(c_buff,buff_index);          //alphabetizes the token before it is compared with the sorted basis string			
				formable_count+=checkWord(c_buff, buff_index+1, basis_str);			
			}
			started_word=false;                      //resets our tracking bool so we can proceed to the next word
			memset(&c_buff[0],0,max_length);
			buff_index=0;
		}
		else if(buff_index >= max_length)            //if a word is longer than the basis string then it automatically isn't formable
		{
			++word_count;
			memset(&c_buff[0],0,max_length);
			buff_index=0;	
		} 
		else
		{
			if(started_word==false) {                //determines if we are at the start of a new token
				started_word=true;
			}
			c_buff[buff_index]=c;                    //appends the current char to partial token 
			++buff_index;					
		}

	} while(c!=EOF);
	free(c_buff);
	fclose(input_file);
	printf("%s","Number of tokenized words read from file: ");
	printf("%d\n",word_count);
	printf("%s","Number of words formable from the basis string: ");
	printf("%d\n",formable_count);
	printf("%s","Percent of formable words: ");
	printf("%f\n",(formable_count / (float) word_count)*100);
}

//main function takes its from the command line
int main (int argc, char **argv) {
	if(argc !=3) {
		printf("%s\n", "first input must be the key string, and second must be the txt file path");
		return 0;
	}
	char* basis_str=argv[1];
	char* fname=argv[2];
	sortStr(basis_str, (int) strlen(basis_str));
	processWordsFromFile(fname, basis_str);
	return 0;
};