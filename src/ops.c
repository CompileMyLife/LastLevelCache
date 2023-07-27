#include "ops.h"

void mode_0(Set* _cache, Cache_Stats* _cache_stats, uint16_t* tag, uint16_t* set, uint8_t* byte_sel) {
    _cache_stats->reads++;

// Find the tag if it exists first Approach
 
    int way = tag_exists(_cache, tag, set);

    if (way <= 8-1 && way != -1) {
        // Check if valid
        if (_cache[*set].valid_b[way] == 1) {
            if (_cache[*set].MESI_b[way] == SHARED   || 
                _cache[*set].MESI_b[way] == MODIFIED ||
                _cache[*set].MESI_b[way] == EXCLUSIVE) {
                // Cache HIT 
                update_LRU(_cache, set, way);
                fprintf(stdout, "CPU READ <HIT> MEM. READ\n");
                _cache_stats->hits++;
                return;
            }
        }
        // The way is INVALID but the tag exists
        else {
            // Cache MISS
            update_LRU(_cache, set, way);
            _cache[*set].MESI_b[way] = EXCLUSIVE;
            _cache[*set].valid_b[way] = 1;
            fprintf(stdout, "CPU READ <MISS> MEM. READ\n");
            _cache_stats->misses++;
            return;
        }
    }
    // The tag does not exist in set
    else {
        // Cache MISS

        // Find the way to evict using LRU_b then update the bits
        // and replace that way
         way = evict_LRU(_cache, tag, set); 
         _cache[*set].MESI_b[way] = EXCLUSIVE;
         _cache[*set].valid_b[way] = 1;
         fprintf(stdout, "CPU READ <MISS> MEM. READ\n");
         _cache_stats->misses++;
         return;
    }
}


// Iterative Approach
            
#if 0
    // Iterate through each way or line
    for (int i = 0; i < 8; i++){
        // Check if valid bit set
        if (_cache[*set].valid_b[i] == 1) {
            if (_cache[*set].tag[i] == *tag) {
                if (    _cache[*set].MESI_b[i] == SHARED   || 
                        _cache[*set].MESI_b[i] == MODIFIED ||
                        _cache[*set].MESI_b[i] == EXCLUSIVE) { // Cache HIT

                    // update_LRU(_cache, &set, i);
                    fprintf(stdout, "CPU READ <HIT> MEM. READ\n");
                    _cache_stats->hits++;
                    return;
                }
            }

            if (_cache[*set].tag[i] != *tag) {
                // evict_LRU(_cache, &set, i);  
                // initiate mem. request to read cache line
                _cache[*set].tag[i] = *tag;
                //_cache[*set].LRU_b[i] = 0x7;        // Set as MRU
                _cache[*set].MESI_b[i] = EXCLUSIVE;

                // deliver data to CPU
                fprintf(stdout, "CPU READ <MISS> MEM. READ\n");
                return;
            }
        }

        if (_cache[*set].valid_b[i] == 0) {
            // initiate mem. request to read cache line
            _cache[*set].valid_b[i] = 1;        // set valid bit
            _cache[*set].tag[i] = *tag;
            _cache[*set].MESI_b[i] = EXCLUSIVE;
            //update_LRU(_cache, &set, i);
            
            // deliver data to CPU
            fprintf(stdout, "CPU READ <MISS> MEM. READ\n");
            _cache_stats->misses++;
            return;
        }
    }
}
#endif

