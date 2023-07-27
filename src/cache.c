#include "cache.h"

Set* create_cache(void) {
    Set* cache;

    // Allocate an array of 32768 sets and initalize each member in set to 0s
    cache = (Set *)calloc(32768, sizeof(Set));
    if (cache == NULL) {
        perror("ERROR: calloc() unable to allocate cache");
        exit(EXIT_FAILURE);
    }

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

    // Initialize correct MESI state and LRU bits for each set in cache
    // Iterate over each set
    for (int i = 0; i < 32768; i++){
        _cache[i].LRU_b = 0x00;          // Set bits to 0 first

        // Iterate over each way or line
        for (int j = 0; j < 8; j++){
            _cache[i].MESI_b[j] = INVALID;
        }
    }
}

int tag_exists(Set* _cache, uint16_t* tag, uint16_t* set) {
    // Iterate over each way to check if the tag exists
    for (int i = 0; i < 8; i++) {
        if (_cache[*set].tag[i] == *tag) {
            return i; // return the way where the tag exists
        }
    }

    // IF there is no tag that exists
    return -1;
}
