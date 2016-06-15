//
//  WordPercentPowerString.h
//

#ifndef WORDPERCENTPOWERSTRING_H
#define WORDPERCENTPOWERSTRING_H

#include "CharTable.h"
#include "SinglyLinkedString.h"
#include "HashMapString.h"
#include "WordSort.h"
#include "Parsing.h"
#include <string.h>

char* base_str;

HashMap* power_set_map; 

#define TABLE_SIZE 128   // Chosen based on the size of the standard ASCII character set

#endif