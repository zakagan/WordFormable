#include "CheckWordByPartials.h"

/* Takes an alphabetized word and an alphabetized base string returns 1 if the word
 can be formed from the base string, 0 otherwise . 

 It does so by grouping each unique char with others like it. For example, all the 'a's 
 will be gathered together into partial_buff. Then, if that partial segment of the token
 exists within the base string, the function will proceed to the next unique char. If the
 partial does not exist then the token is not formable */
unsigned char checkWord(const char *token_str, const char *base_str, char *partial_buff, const unsigned int str_length) 
{	
	char cur_char, next_char;
	const char *base_pointer=base_str;
	unsigned int word_index=0, partial_index;	
	do{	
		partial_index=0;
		do{	
			cur_char= token_str[word_index];
			next_char= token_str[word_index+1];		
			partial_buff[partial_index]=cur_char;    //adds each repeated char to partial_buff
			++partial_index;
			++word_index;
		} while(cur_char==next_char);
		base_pointer=strstr(base_pointer, partial_buff);       //Updates starting point for comparision, to reduce redundent checks
		memset(&partial_buff[0],0,str_length * sizeof(char));  //resets partial_buff so it can collect the instances of the next char
		if(!base_pointer)                                      //checks if all instances of this char can be found within the base
		{
			return 0;                                   //result if partial_buff could not be found in the base
		}
	} while(next_char!='\0');
	return 1;
}
