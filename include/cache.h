#ifndef __CACHE_H
#define __CACHE_H

#include <stdint.h>

typedef struct cache_stats {
    uint64_t reads;
    uint64_t writes;
    uint64_t hits;
    uint64_t misses;
    float hit_ratio;
} llc_stats;

#endif
