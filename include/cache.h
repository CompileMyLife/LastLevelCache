#ifndef __CACHE_H
#define __CACHE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

typedef enum __MESI_b{
    MODIFIED  = 3,
    EXCLUSIVE = 2,
    SHARED    = 1,
    INVALID   = 0
} _MESI_b;

typedef struct __cache_stats {
    uint64_t reads;
    uint64_t writes;
    uint64_t hits;
    uint64_t misses;
    float    hit_ratio;
    float    miss_ratio;
} Cache_Stats;

// Template for a set of the Cache
typedef struct __set {
    // Do not need to fill cache lines since no data provided just simulated
    //uint8_t  line[8][64];
    uint32_t address;
    uint16_t tag[8];
    uint8_t  valid_b[8];
    //uint8_t  dirty_b[8]; 
    uint8_t  LRU_b; 
    _MESI_b  MESI_b[8];
} Set;

// Allocate 32768 sets in creation of the Cache
// Returns an array/ptr of `Set` structs
Set* create_cache(void);

// Frees up allocated `Set`s 
void delete_cache(Set* _cache);

// Initialize the Cache to certain state and Cache Statistics to 0
void init_cache(Set* _cache, Cache_Stats* _cache_stats);

// Reset Cache to default state as in init_cache()
void reset_cache(Set* _cache);

// Check if a matching tag exists in Cache given the tag and set
// Returns the way if a tag exists else a -1 if no tag exists
int tag_exists(Set* _cache, uint16_t* tag, uint16_t* set);

// Check if an empty way is located in set of the Cache
// Returns the empty way else a -1 if no empty way
int empty_way(Set* _cache, uint16_t* set, int way);

// Print out all valid cache lines/ways
void print_cache_content(Set* _cache);
#endif
