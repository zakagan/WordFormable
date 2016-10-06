#include "WordFormableTable.h"

/* The char being examined is decremented from the comparison table. If the table has run out of that
 character then the function will report that the word is not formable*/
unsigned char checkChar(const char c, Table *comparison_table)
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
void processTokensFromFile(char** base_array, const char** fname_array, const unsigned int num_inputs, const unsigned int* length_array, \
    const unsigned int max_length, const unsigned char silence, const unsigned char tare_setup, const size_t buckets)
 {
    unsigned int char_count, word_count, formable_count, buff_index;
    FILE *input_file;
    char *c_buff=NULL;
    int c;                                             //character returned from fgetc
    Table *base_table, *comparison_table;
    unsigned char is_formable;                 
    unsigned int* index;

    c_buff= calloc(max_length+1, sizeof(char));     //used to build word tokens as read from the provided file
    if (c_buff==NULL){
        printf("Memory allocation failed: char pointer c_buff\n");
        exit(0);
    }

    base_table=tableCreate(TABLE_SIZE);
    comparison_table=tableCreate(TABLE_SIZE);

    fillTable(base_table, base_array[0]);
    index=generateIndex(base_table);                         //used to rebuild only the necessary parts of the table
    copyTableFromIndex(comparison_table, base_table, index);

    
    if (!tare_setup) {
        for(unsigned int i=0; i<num_inputs; ++i) {
            char_count=0, word_count=0, formable_count=0, buff_index=0;
            is_formable=1;                                //assume token is formable until checkChar returns otherwise  
            
            input_file= fopen(fname_array[i], "r");                 
            if(input_file==NULL) {                          //Prevents seg fault crash if there is a problem with the provided file
                printf("Improper file name: %s\n",fname_array[i]);
                continue;
            }

            if(!silence) {
                displayIntro(i+1,fname_array[i]);
            }

            do{
                c = fgetc(input_file);                       //gets next character
                if(isTokenizer(c) || c==EOF) {          
                    if(buff_index != 0){                        //non-negative index + reaching a tokenizer means c_buff contains a token
                        ++word_count;
                        char_count += buff_index+1;         // +1 to account for the tokenizing character causing termination of token reading
                        if(is_formable) {            
                            ++formable_count;
                            if (!silence) {printf("\t%s\n",c_buff);}
                        } 
                        //reset params for next loop and next token
                        buff_index=0, is_formable=1;           
                        copyTableFromIndex(comparison_table, base_table,index);    
                        memset(&c_buff[0],0,(buff_index < max_length) ? buff_index : max_length);        
                    }
                    else {
                        ++char_count;       // A tokenizer char has been found, but no token is being formed
                    }          
                }
                else
                {
                    if(is_formable) { 
                        if(checkChar(c,comparison_table)) {  
                            c_buff[buff_index]=c; 
                        } else {
                            is_formable=0;
                        }    
                    } 
                    ++buff_index;
                }

            } while(c!=EOF);
            --char_count;       //correct for EOF being read for a char
            fclose(input_file);
            reportResults(length_array[0],char_count, word_count, formable_count);
        }
    }    

    tableDestroy(base_table);
    tableDestroy(comparison_table);
    indexDestroy(index);
    free(c_buff);

}
