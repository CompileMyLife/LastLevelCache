#include "ops.h"

void mode_0(Set* _cache, Cache_Stats* _cache_stats, uint16_t* tag, uint16_t* set, uint8_t* byte_sel) {
    _cache_stats->reads++;
    
    // Iterate through each way or line
    for (int i = 0; i < 8; i++){
        // Check if valid bit set
        if (_cache[*set].valid_b[i] == 1) {
            if ((_cache[*set].tag[i] == *tag) && (_cache[*set].MESI_b[i] != INVALID)){  // Cache HIT
                // INVALID -> SHARED
                _cache[*set].MESI_b[i] = SHARED;

                // deliver data to CPU
                fprintf(stdout, "CPU READ <HIT> MEM. READ\n");
                _cache_stats->hits++;
                return;
            }

            if ((_cache[*set].tag[i] != *tag) && (_cache[*set].LRU_b[i] < 0)) {
                // evict_LRU(_cache, &set, way);  
                // initiate mem. request to read cache line
                _cache[*set].tag[i] = *tag;
                _cache[*set].LRU_b[i] = 0x7;        // Set as MRU
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
            //update_LRU(_cache, &set, way);
            
            // deliver data to CPU
            fprintf(stdout, "CPU READ <MISS> MEM. READ\n");
            return;
        }
    }
}
