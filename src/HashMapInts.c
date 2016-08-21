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
    m->map = calloc(size, sizeof(unsigned char));
    if (m->map==NULL){
        printf("Memory allocation failed: unsigned char pointer m->map\n");
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
 Collisions are not counted, there is no chaining */
void hashMapUpdate(HashMap* m, const char* str)
{
    size_t h;
    h = communicativeStringHash(str) % m->size;
    if (!m->map[h]) {
        m->map[h]=(unsigned char) 1;     //Sets 1 byte size validity element equal to an casted unsigned char 1
    }
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