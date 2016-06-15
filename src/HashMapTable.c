#include "HashMapTable.h"

// Hash function used to store nodes based on their strings
size_t djb2TableHash(const Table* t) {
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
    m->map = calloc(size, sizeof(int));
    assert(m->map != 0);

    return m;
}

// Frees memory used for a hash map
void hashMapDestroy(HashMap* m)
{
    free(m->map);
    free(m);
}

/* Updates the validity integer at a hash map entry determined by the hash function.
 Collisions only result in an increased ineteger count for its respective hash entry,
 there is no chaining */
void hashMapInsert(HashMap* m, Node* n)
{
    size_t h;
    h = djb2TableHash(n->T) % m->size;
    //printf("Hash insert at %zu out of %d\n", h, m->size);
    m->map[h] += 1;                 //keeps tally of entries to this location on the hash map
}

// returns 1 if the character table exists in hash table, returns 0 otherwise
int checkHashMapEntry(const HashMap* m, const Table* char_table) {
    size_t h;
    h = djb2TableHash(char_table) % m->size;
    if(m->map[h]) {
            return 1;
    } else {
        return 0;
    }
}
