#ifndef __CACHE_H
#define __CACHE_H

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

typedef struct __cache_stats {
    uint64_t reads;
    uint64_t writes;
    uint64_t hits;
    uint64_t misses;
    float hit_ratio;
} Cache_Stats;

typedef struct __set {
    uint8_t line0[64];
    uint8_t line1[64];
    uint8_t line2[64];
    uint8_t line3[64];
    uint8_t line4[64];
    uint8_t line5[64];
    uint8_t line6[64];
    uint8_t line7[64];

    uint16_t tag[8];
    uint8_t  valid_b;
    uint8_t  dirty_b; 
    uint8_t  LRU_b; 
} Set;

Set* create_cache(void);

void delete_cache(Set* _cache);

void init_cache(Set* _cache, Cache_Stats* _cache_stats);

bool cache_read(uint32_t address);

bool cache_write(uint32_t address);

#endif
