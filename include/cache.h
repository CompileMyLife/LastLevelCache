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
} Cache_Stats;

typedef struct __set {
    // Do not need to fill cache lines since no data provided just simulated
    //uint8_t  line[8][64];
    uint16_t tag[8];
    uint8_t  valid_b[8];
    //uint8_t  dirty_b[8]; 
    uint8_t  LRU_b; 
    _MESI_b  MESI_b[8];
} Set;

Set* create_cache(void);

void delete_cache(Set* _cache);

void init_cache(Set* _cache, Cache_Stats* _cache_stats);

int tag_exists(Set* _cache, uint16_t* tag, uint16_t* set);

void print_cache_stats(Cache_Stats* _cache_stats, uint8_t* n, bool* mode);

#endif
