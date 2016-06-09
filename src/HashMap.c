#include "HashMap.h"

// Hash function used to store nodes based on their strings
size_t djb2Hash(const Table* t) {
	size_t hash = 5381;
	int i, j;
	for (i=0; i < t->size; i++) {
        for(j=0; j < t->array[i]; j++) {
		  hash = ((hash << 5) + hash) ^ i;
        }
	}
	return hash;
}

// Creates memory space for a hash map of character & their frequency values within the base string
HashMap* hashMapCreate(const size_t size)
{
    HashMap* m;

    m = malloc(sizeof(HashMap));
    assert(m != 0);

    m->size = size;
    m->map = calloc(m->size, sizeof(Node*));
    assert(m->map != 0);

    return m;
}

// Frees memory used for a hash map
void hashMapDestroy(HashMap* m)
{
    int i;
    for(i=0; i < m->size; i++) {
    	if(m->map[i]) {
    		destroyStack(m->map[i]);
    	}
    }
    free(m->map);
    free(m);
}

// inserts a new entry into the hash map structure
void hashMapInsert(HashMap* m, Node* n)
{
    size_t h;
    Node* chained_entry;
    h = djb2Hash(n->T) % m->size;
    //printf("Hash insert at %zu out of %d\n", h, m->size);
    chained_entry = m->map[h];      //this hash table uses chaining to resolve collisons
    if (chained_entry==0) {
		push(&m->map[h], n->T, 0);
	} else {
		while(chained_entry) {
			if(compareTable(chained_entry->T, n->T) ) {
                //printf("\t\t Duplicate Detected!\n");
				return;   // Duplicate are not added again to the chain
			}
			chained_entry = chained_entry->next;
		}
        //printf("\t\t Collison Detected!\n");
		push(&m->map[h], n->T, 0);
	} 
}

// returns 1 if the character table exists in hash table, returns 0 otherwise
int checkHashMapForTable(const HashMap* m, const Table* char_table) {
    size_t h;
    Node* chained_entry;
    h = djb2Hash(char_table) % m->size;
    chained_entry = m->map[h];
    while(chained_entry) {
        if (compareTable(chained_entry->T, char_table)) {
            return 1;
        }
        chained_entry = chained_entry->next;
    }
    return 0;
}
