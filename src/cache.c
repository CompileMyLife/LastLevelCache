#include "cache.h"

Set* create_cache(void) {
    Set* cache;

    // Allocate an array of 32768 sets and initalize each member in set to 0s
    cache = (Set *)calloc(32768, sizeof(Set));
    
    return cache; 
}

void delete_cache(Set* cache) {
    free(cache);
}

void init_cache(Set* _cache, Cache_Stats* _cache_stats) {
    // Initialize all stats variables
    _cache_stats->reads     = 0;
    _cache_stats->writes    = 0;
    _cache_stats->hits      = 0;
    _cache_stats->misses    = 0;
    _cache_stats->hit_ratio = 0;

    // TODO: Initialize correct MESI and LRU bits for each sit in cache
}
