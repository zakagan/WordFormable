#include "HashMapInts.h"

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
    m->map = calloc(size, sizeof(unsigned int));
    if (m->map==NULL){
        printf("Memory allocation failed: unsigned int pointer m->map\n");
        exit(0);
    }

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
void hashMapUpdate(HashMap* m, const char* str)
{
    size_t h;
    h = communicativeStringHash(str) % m->size;
    m->map[h]++;                 //keeps tally of entries to this location on the hash map
}

// returns 1 if the character table exists in hash table, returns 0 otherwise
int checkValidityHashMap(const HashMap* m, const char* str) {
    size_t h;
    h = communicativeStringHash(str) % m->size;
    if(m->map[h]) {
            return 1;
    } else {
        return 0;
    }
}