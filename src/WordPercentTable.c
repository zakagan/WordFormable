#include <stdlib.h>
#include <stdio.h>

#include "WordPercentTable.h"

/* The char being examined is decremented from the comparison table. If the table has run out of that
 character then the function will report that the word is not formable*/
int checkChar(char c)
{
    if (comparison_table->array[(unsigned char) c]>0)
    {
        comparison_table->array[(unsigned char) c]--;
        return 1;
    }
    else 
    {
        return 0;
    }
}

/* opens the provided txtfile, and compares each letter with a table of letters from the base string. 
The function keeps track of whether or not the word is formable. Then when a tokenizer is found the 
word counter updates, and so does the formable word counter, depernding on its status */
void processCharsFromFile(char *fname, int max_length)
 {
    FILE *input_file;                                  //used to construct token from read characters
    int char_count=0, word_count=0, formable_count=0;
    int buff_index=0, is_formable=1;                   //assume token is formable until checkChar returns otherwise  
    int c;                                             //character returned from fgetc

    input_file= fopen(fname, "r");
    do{
        c = fgetc(input_file);                       //gets next character
        if(isTokenizer(c) || c==EOF) {          
            if(buff_index>0){                        //non-negative index + reaching a tokenizer means c_buff contains a token
                ++word_count;
                char_count += buff_index;
                if(is_formable) {            
                    ++formable_count;
                }       
            }
            buff_index=0, is_formable=1;           
            copyTable(comparison_table, base_table);        //resets the table used for comparisons to be used w next token
        }
        else
        {
            if(is_formable) { 
                is_formable=checkChar(c);        
            } 
            ++buff_index;
        }

    } while(c!=EOF);

    fclose(input_file);
    reportResults(max_length, char_count, word_count, formable_count);
}

// main function which takes its inputs from the command line
int main (int argc, char **argv) {
    int max_length;                                   // Based on length taken from the base string
    if(argc !=3) {
        printf("%s\n", "first input must be the base string, and second must be the txt file path");
        return 0;
    }
    char *fname, *base_str;
    base_str=argv[1];
    fname=argv[2];
    max_length= strlen(base_str);

    base_table=tableCreate(TABLE_SIZE);
    comparison_table=tableCreate(TABLE_SIZE);
    fillTable(base_table, base_str);
    copyTable(comparison_table, base_table); 

    processCharsFromFile(fname,max_length);
    
    tableDestroy(base_table);
    tableDestroy(comparison_table);

    return 0;
}