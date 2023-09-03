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

void reset_cache(Set* _cache) {
    // Reinitialize the MESI states to INVALID, LRU bits to 0x00 and the tag to
    // 0 for each set in cache
    for (int i = 0; i < 32768; i++){
        _cache[i].LRU_b = 0x00;

        // Iterate over each way or line
        for (int j = 0; j < 8; j++){
            _cache[i].MESI_b[j] = INVALID;
            _cache[i].tag[j]    = 0;
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
    // ELSE no tag exists
    return -1; 
}

int empty_way(Set* _cache, uint16_t* set, int way) {
    // Iterate over each way to check if there is any empty ways
    for (int i = 0; (i < 8) && (way < 0); i++) {
        if (_cache[*set].valid_b[i] == 0) {
            way = i; // set the way where the empty slot is located at
        }
    }
    
    if (way >= 0) {
        return way; // return the empty way
    }
    else {
        return -1; // not empty way
    }
}

void print_cache_content(Set* _cache) {
    for (int idx = 0; idx < 32768; idx++) {
        for (int way = 0; way < 8; way++) {
            if (_cache[idx].valid_b[way]) {
                fprintf(stdout, "idx = %d, way = %d, tag = %X, MESI = %d, LRU = %d\n",
                        idx, way, _cache[idx].tag[way], _cache[idx].MESI_b[way], 
                        _cache[idx].LRU_b);
            }
        }
    }
}
