#include "ops.h"

// Read request from L1 data cache
void mode_0(Set* _cache, Cache_Stats* _cache_stats, uint32_t* addr, uint16_t* tag, uint16_t* set) {
    _cache_stats->reads++;

// Find the tag if it exists first Approach
 
    int way = tag_exists(_cache, tag, set);

    if (way != -1) {
        // Check if valid
        switch(_cache[*set].MESI_b[way]) {
            case SHARED:
                update_LRU(_cache, set, way);
                _cache[*set].valid_b[way] = 1;
                _cache_stats->hits++;
                return;

            case MODIFIED:
                update_LRU(_cache, set, way);
                _cache[*set].valid_b[way] = 1;
                _cache_stats->hits++;
                return;

            case EXCLUSIVE:
                update_LRU(_cache, set, way);
                _cache[*set].valid_b[way] = 1;
                _cache_stats->hits++;
                return;

            case INVALID: // The way is INVALID but the tag exists
            default:
                operate_bus("READ", addr);
                update_LRU(_cache, set, way);
                if (get_snoop_result(addr) == HIT || get_snoop_result(addr) == HITM) {
                    _cache[*set].MESI_b[way] = SHARED;
                    _cache[*set].valid_b[way] = 1;
                    _cache_stats->misses++;
                    return;
                }
                else if (get_snoop_result(addr) == NOHIT) {
                    _cache[*set].MESI_b[way] = EXCLUSIVE;
                    _cache[*set].tag[way] = *tag;
                    _cache[*set].valid_b[way] = 1;
                    _cache_stats->misses++;
                    return;
                }
        } 
    }
// TODO: NEED TO FIX
    // The tag does not exist in set
    else {
        // Cache MISS
        way = empty_way(_cache, set, way);  // check if 

        // Empty slot
        if (way != -1) {
            // Cache MISS
            update_LRU(_cache, set, way);
            _cache[*set].tag[way] = *tag;
            _cache[*set].MESI_b[way] = EXCLUSIVE; // INVALID->EXCLUSIVE
            _cache[*set].valid_b[way] = 1;
            _cache_stats->misses++;
            return;
        }
        // tag is different from the parsed tag in set
        else {
            // Find the way to evict using LRU_b then update the bits
            // and replace that way
            way = evict_LRU(_cache, tag, set); 
            _cache[*set].MESI_b[way] = EXCLUSIVE;  // INVALID->EXCLUSIVE
            _cache[*set].valid_b[way] = 1;
            _cache_stats->misses++;
            return;
        }
    }
}


// Write request form L1 data cache
void mode_1(Set* _cache, Cache_Stats* _cache_stats, uint32_t* addr, uint16_t* tag, uint16_t* set) {
    _cache_stats->writes++;

    int way = tag_exists(_cache, tag, set);
 
    if (way != -1) {
        // Check if valid
        switch(_cache[*set].MESI_b[way]) {
            case SHARED:
                // Cache HIT 
                _cache[*set].MESI_b[way] = MODIFIED;
                _cache[*set].valid_b[way] = 1;
                update_LRU(_cache, set, way);
                operate_bus("INVALIDATE", addr);
                _cache_stats->hits++;
                return;

            case MODIFIED:
                // Cache HIT 
                _cache[*set].MESI_b[way] = MODIFIED;
                _cache[*set].valid_b[way] = 1;
                update_LRU(_cache, set, way);
                _cache_stats->hits++;
                return;

            case EXCLUSIVE:
                // Cache HIT 
                _cache[*set].MESI_b[way] = MODIFIED;
                _cache[*set].valid_b[way] = 1;
                update_LRU(_cache, set, way);
                _cache_stats->hits++;
                return;

            // The way is INVALID but the tag exists
            case INVALID:
            default:
                // Cache MISS
                update_LRU(_cache, set, way);
                _cache[*set].MESI_b[way] = MODIFIED; // INVALID->MODIFIED
                _cache[*set].valid_b[way] = 1;
                operate_bus("RWIM", addr);
                _cache_stats->misses++;
                return;
        }
    }
// TODO: NEED TO FIX
    // The tag does not exist in set
    else {
        // Cache MISS
        way = empty_way(_cache, set, way);

        // Empty Slot
        if (way != -1) {
            // Cache MISS
            update_LRU(_cache, set, way);
            _cache[*set].tag[way] = *tag;
            _cache[*set].MESI_b[way] = EXCLUSIVE; // INVALID->EXCLUSIVE
            _cache[*set].valid_b[way] = 1;
            _cache_stats->misses++;
            return;
        }
        // tag is different from the parsed tag in set
        else {
            // Find the way to evict using LRU_b then update the bits
            // and replace that way
             way = evict_LRU(_cache, tag, set); 
             _cache[*set].MESI_b[way] = MODIFIED;  // INVALID->MODIFIED
             _cache[*set].valid_b[way] = 1;
             _cache_stats->misses++;
             return;
        }
    }
}

// read request from L1 instruction cache
void mode_2(Set* _cache, Cache_Stats* _cache_stats, uint32_t* addr, uint16_t* tag, uint16_t* set) {
    _cache_stats->reads++;

    int way = tag_exists(_cache, tag, set);

    if (way != -1) {
        // Check if valid
        switch(_cache[*set].MESI_b[way]) {
            case SHARED:
                update_LRU(_cache, set, way);
                _cache[*set].valid_b[way] = 1;
                _cache_stats->hits++;
                return;

            case MODIFIED:
                update_LRU(_cache, set, way);
                _cache[*set].valid_b[way] = 1;
                _cache_stats->hits++;
                return;

            case EXCLUSIVE:
                update_LRU(_cache, set, way);
                _cache[*set].valid_b[way] = 1;
                _cache_stats->hits++;
                return;

            case INVALID: // The way is INVALID but the tag exists
            default:
                operate_bus("READ", addr);
                update_LRU(_cache, set, way);
                if (get_snoop_result(addr) == HIT || get_snoop_result(addr) == HITM) {
                    _cache[*set].MESI_b[way] = SHARED;
                    _cache[*set].valid_b[way] = 1;
                    _cache_stats->misses++;
                    return;
                }
                else if (get_snoop_result(addr) == NOHIT) {
                    _cache[*set].MESI_b[way] = EXCLUSIVE;
                    _cache[*set].valid_b[way] = 1;
                    _cache_stats->misses++;
                    return;
                }
        } 
    }
// TODO: NEED TO FIX
    // The tag does not exist in set
    else {
        // Cache MISS
        way = empty_way(_cache, set, way);  // check if 

        // Empty slot
        if (way != -1) {
            // Cache MISS
            update_LRU(_cache, set, way);
            _cache[*set].tag[way] = *tag;
            _cache[*set].MESI_b[way] = EXCLUSIVE; // INVALID->EXCLUSIVE
            _cache[*set].valid_b[way] = 1;
            _cache_stats->misses++;
            return;
        }
        // tag is different from the parsed tag in set
        else {
            // Find the way to evict using LRU_b then update the bits
            // and replace that way
            way = evict_LRU(_cache, tag, set); 
            _cache[*set].MESI_b[way] = EXCLUSIVE;  // INVALID->EXCLUSIVE
            _cache[*set].valid_b[way] = 1;
            _cache_stats->misses++;
            return;
        }
    }
}

// Snooped invalidate command
void mode_3(Set* _cache, Cache_Stats* _cache_stats, uint32_t* addr, uint16_t* tag, uint16_t* set) {
    // Find the matching tag's way in cache
    int way = tag_exists(_cache, tag, set);

    if (way != -1) {
        if (_cache[*set].MESI_b[way] == SHARED) {
            update_LRU(_cache, set, way);
            _cache[*set].MESI_b[way] = INVALID;
            put_snoop_result(addr, HIT);
            msg_to_cache("INVALIDATELINE", addr);
            return;
        }
        else if (_cache[*set].MESI_b[way] == INVALID) {
            _cache[*set].MESI_b[way] = INVALID;
            put_snoop_result(addr, NOHIT);
            return;
        }
    }

    else {
        put_snoop_result(addr, NOHIT); // NOHIT
        return;
    }
}

// Snooped read request
void mode_4(Set* _cache, Cache_Stats* _cache_stats, uint32_t* addr, uint16_t* tag, uint16_t* set) {
    _cache_stats->reads++;

    // Find the matching tag's way in cache
    int way = tag_exists(_cache, tag, set);

    if (way != -1) {
        if (_cache[*set].MESI_b[way] == MODIFIED) {
            _cache[*set].MESI_b[way] = SHARED;
            put_snoop_result(addr, HITM);
            operate_bus("WRITE", addr);
            return; 
        }
        else if (_cache[*set].MESI_b[way] == EXCLUSIVE) {
            _cache[*set].MESI_b[way] = SHARED;
            put_snoop_result(addr, HIT);
            return;
        }
        else if (_cache[*set].MESI_b[way] == SHARED) {
            _cache[*set].MESI_b[way] = SHARED;
            put_snoop_result(addr, HIT);
            return;
        }

        else {
            _cache[*set].MESI_b[way] = INVALID;
            return;
        } 
    }

    else {
        put_snoop_result(addr, NOHIT); // NOHIT
        return;
    }
}

// Snooped write request
void mode_5(Set* _cache, Cache_Stats* _cache_stats, uint32_t* addr, uint16_t* tag, uint16_t* set) {
    _cache_stats->writes++;

    // Find the matching tag's way in cache
    int way = tag_exists(_cache, tag, set);

    if (way != -1) {
        if (_cache[*set].MESI_b[way] == SHARED) {
            _cache[*set].MESI_b[way] = INVALID;
            return;
        }
        else if (_cache[*set].MESI_b[way] == MODIFIED) {
            _cache[*set].MESI_b[way] = INVALID;
            return;
        }
        else if (_cache[*set].MESI_b[way] == EXCLUSIVE) {
            _cache[*set].MESI_b[way] = INVALID;
            return;
        }
        else {
            _cache[*set].MESI_b[way] = INVALID;
            put_snoop_result(addr, NOHIT);
            return;
        }
    }
    else {
        put_snoop_result(addr, NOHIT); // NOHIT
        return;
    }
}

// Snooped read with intent to modify request
void mode_6(Set* _cache, Cache_Stats* _cache_stats, uint32_t* addr, uint16_t* tag, uint16_t* set) {
    _cache_stats->reads++;

    // Find the matching tag's way in cache
    int way = tag_exists(_cache, tag, set);

    if (way != -1) {
        if (_cache[*set].MESI_b[way] == SHARED) {
            update_LRU(_cache, set, way);
            _cache[*set].MESI_b[way] = INVALID;
            put_snoop_result(addr, HIT);
            msg_to_cache("INVALIDATELINE", addr);
            return;
        }
            
        else if (_cache[*set].MESI_b[way] == MODIFIED) {
            update_LRU(_cache, set, way);
            _cache[*set].MESI_b[way] = INVALID;
            put_snoop_result(addr, HITM);
            operate_bus("WRITE", addr);
            msg_to_cache("GETLINE", addr);
            return;
        }
        else if (_cache[*set].MESI_b[way] == EXCLUSIVE) {
            update_LRU(_cache, set, way);
            _cache[*set].MESI_b[way] = INVALID;
            put_snoop_result(addr, HIT);
            msg_to_cache("SENDLINE", addr);
            return;
        }

        else {
            _cache[*set].MESI_b[way] = INVALID;
            put_snoop_result(addr, NOHIT);
            return;
        }
    }
    else {
        put_snoop_result(addr, NOHIT); // NOHIT
        return;
    }
}

// Clear the cache and reset all state
void mode_8(Set* _cache) {
   fprintf(stdout, "Clearing the cache and resetting all states\n");
   reset_cache(_cache);
}

// Print the contents and state of each valid cache line
void mode_9(Set* _cache) {
   print_cache_content(_cache);
}
