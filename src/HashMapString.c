#include "HashMapString.h"

// Creates memory space for a hash map of character & their frequency values within the base string
HashMap* hashMapCreate(const size_t size)
{
    HashMap* m;

    m = malloc(sizeof(HashMap));
    if (m==NULL){
        printf("Memory allocation failed: HashMap pointer m\n");
        exit(0);
    }

    m->size = size;
    m->map = calloc(size, sizeof(Node*));
    if (m->map==NULL){
        printf("Memory allocation failed: Node pointer pointer m->Map\n");
        exit(0);
    }

    return m;
}

// Frees memory used for a hash map
void hashMapDestroy(HashMap* m)
{
    unsigned int i;
    for(i=0; i < m->size; i++) {
    	if(m->map[i]) {
    		destroyStack(m->map[i]);
    	}
    }
    free(m->map);
    free(m);
}

/* inserts a new entry into the hash map structure, 
 returns 1 if there is a collision, 0 otherwise */
unsigned char hashMapInsert(HashMap* m, Node* n)
{
    size_t h;
    Node* chained_entry;
    h = communicativeStringHash(n->S) % m->size;
    chained_entry = m->map[h];      //this hash table uses chaining to resolve collisions
    if (chained_entry==0) {
		push(&m->map[h], n->S, n->length, 0);
        return 0;
	} else {
		while(chained_entry != 0) {
			if(strncmp(n->S, chained_entry->S,n->length) == 0) {
				//printf("\t%s\n", " Duplicate detected!");
				return 0;   // Duplicate are not added again to the chain
			}
			chained_entry = chained_entry->prev;
		}
		//printf("\t%s\n", " Collision detected!");
		push(&m->map[h], n->S, n->length,0);
        return 1;
	} 
}

// if a string's hash map entry has a node present returns a pointer to it, returns 0 otherwise
Node* collectHashMapEntry(const HashMap* m, const char* cstring, const int str_length) {
    size_t h;
    Node* chained_entry;
    h = communicativeStringHash(cstring) % m->size;
    chained_entry = m->map[h];
    if(chained_entry) {
        return chained_entry;
    } else {
        return 0;
    }
}
