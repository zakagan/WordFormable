//
//  WordPercentPowerTable.h
//

#ifndef WORDPERCENTPOWERTABLE_H
#define WORDPERCENTPOWERTABLE_H

#include "CharTable.h"
#include "SinglyLinkedTable.h"
#include "HashMapTable.h"
#include "Parsing.h"
#include <string.h>

Table* base_str_table;

HashMap* power_set_map; 

#define TABLE_SIZE 128   // Chosen based on the size of the standard ASCII character set

#endif