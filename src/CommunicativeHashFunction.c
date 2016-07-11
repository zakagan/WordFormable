#include "CommunicativeHashFunction.h"

/* Hash function used to store nodes based on their strings. Results with the same collection of letters
 are hashed to the same value, regardless of ordering, hence it is communicative. */
size_t communicativeStringHash(const char* str) {
    size_t hash = 5381;
    int c;
    while ((c=*str++)) {
        hash = hash ^ (c * 109);
    }
    return hash;
}
