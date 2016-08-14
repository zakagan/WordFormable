#include "WordFormableTable.h"

/* The char being examined is decremented from the comparison table. If the table has run out of that
 character then the function will report that the word is not formable*/
int checkChar(const char c, Table *comparison_table)
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
void processTokensFromFile(char* base_str, FILE* input_file, char* c_buff, const unsigned int max_length, const unsigned int silence, const int buckets)
 {
    int char_count=0, word_count=0, formable_count=0;
    int buff_index=0, is_formable=1;                   //assume token is formable until checkChar returns otherwise  
    int c;                                             //character returned from fgetc
    Table *base_table, *comparison_table;
    unsigned char* index;

    base_table=tableCreate(TABLE_SIZE);
    comparison_table=tableCreate(TABLE_SIZE);

    fillTable(base_table, base_str);
    index=generateIndex(base_table);                         //used to rebuild only the necessary parts of the table
    copyTableFromIndex(comparison_table, base_table, index);

    do{
        c = fgetc(input_file);                       //gets next character
        if(isTokenizer(c) || c==EOF) {          
            if(buff_index>0){                        //non-negative index + reaching a tokenizer means c_buff contains a token
                ++word_count;
                char_count += buff_index;
                if(is_formable) {            
                    ++formable_count;
                    if (!silence) {printf("%s\n",c_buff);}
                }       
            }
            //reset params for next loop and next token
            buff_index=0, is_formable=1;           
            copyTableFromIndex(comparison_table, base_table,index);    
            memset(&c_buff[0],0,max_length);             
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

    tableDestroy(base_table);
    tableDestroy(comparison_table);
    indexDestroy(index);

    reportResults(max_length, char_count, word_count, formable_count);
}
