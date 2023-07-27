#ifndef __PLRU_H
#define __PLRU_H

#include <stdint.h>
#include <stdio.h>

#include "cache.h"

// Checks if the bitn == 0 then returns 0 else it returns 1 if bitn == 1
int check_bit(uint8_t num, uint8_t bitn);

// Returns the way that needs to be evicted and replaces that way
// NOTE: Sets the bit if taking LEFT path
//      and Clears the bit if taking RIGHT path
int evict_LRU(Set* _cache, uint16_t* tag, uint16_t* set);

// Search for the way accessed and updates the LRU bits
// NOTE: Clears the bit if taking LEFT path 
//      and Sets the bit if taking RIGHT path
void update_LRU(Set* _cache, uint16_t* set, int way);

#endif
