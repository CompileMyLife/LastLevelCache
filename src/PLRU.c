#include "PLRU.h"

// Checks if the bitn == 0 
// Returns 0 else it returns 1 if bitn == 1
int check_bit(uint8_t num, uint8_t bitn) {
    // Check IF bitn == 1
    if (num & (1 << bitn)) {
        return 1;
    }
    // ELSE bitn == 0
    else {
        return 0;
    }
}

// Returns the way that needs to be evicted and replaces that way
// NOTE: Sets the bit if taking LEFT path
//      and Clears the bit if taking RIGHT path
int evict_LRU(Set* _cache, uint16_t* tag, uint16_t* set) {
    // Check IF bit 0 == 0
    if (!check_bit(_cache[*set].LRU_b, 0)) {
        _cache[*set].LRU_b |= (1 << 0); // set bit 0

        // Check IF bit 1 == 0
        if (!check_bit(_cache[*set].LRU_b, 1)) {
            _cache[*set].LRU_b |= (1 << 1); // set bit 1
            
            // Check IF bit 3 == 0
            if (!check_bit(_cache[*set].LRU_b, 3)) { 
                _cache[*set].LRU_b |= (1 << 3); // set bit 3

                // Evict and replace way 0
                _cache[*set].tag[0] = *tag;
                return 0;
            }
            else {
                _cache[*set].LRU_b &= ~(1 << 3); // clear bit 3

                // ELSE evict and replace way 1
                _cache[*set].tag[1] = *tag;
                return 1;
            }
        }
        else {

            _cache[*set].LRU_b &= ~(1 << 1); // clear bit 1

            // ELSE Check IF bit 4 == 0 
            if (!check_bit(_cache[*set].LRU_b, 4)) {
                _cache[*set].LRU_b |= (1 << 4); // set bit 4
                
                // Evict and replace way 2
                _cache[*set].tag[2] = *tag;
                return 2;
            }
            else {
                _cache[*set].LRU_b &= ~(1 << 4); // clear bit 4

                // ELSE evict and replace way 3
                _cache[*set].tag[3] = *tag;
                return 3;
            }
        }
    }
    else {
        _cache[*set].LRU_b &= ~(1 << 0); // clear bit 0

        // ELSE Check IF bit 2 == 0
        if (!check_bit(_cache[*set].LRU_b, 2)) {
            _cache[*set].LRU_b |= (1 << 2); // set bit 2

            // Check IF bit 5 == 0
            if (!check_bit(_cache[*set].LRU_b, 5)) {
                _cache[*set].LRU_b |= (1 << 5); // set bit 5

                // Evict and replace way 4
                _cache[*set].tag[4] = *tag;
                return 4;
            }
            else {
                _cache[*set].LRU_b &= ~(1 << 5); // clear bit 5

                // ELSE evict and replace way 5
                _cache[*set].tag[5] = *tag;
                return 5;
            }
        }
        else {
            _cache[*set].LRU_b &= ~(1 << 2); // clear bit 2

            // ELSE Check IF bit 6 == 0
            if (!check_bit(_cache[*set].LRU_b, 6)) {
                _cache[*set].LRU_b |= (1 << 6); // set bit 6

                // Evict and replace way 6
                _cache[*set].tag[6] = *tag;
                return 6;
            }
            else { 
                 _cache[*set].LRU_b &= ~(1 << 6); // clear bit 6

                // ELSE evict and replace way 7
                _cache[*set].tag[7] = *tag;
                return 7;
            }
        }
    }
}

// Search for the way accessed and updates the LRU bits
// NOTE: Clears the bit if taking LEFT path 
//      and Sets the bit if taking RIGHT path
void update_LRU(Set* _cache, uint16_t* set, int way) {     
    switch(way) {
        case 0:  // way 0
            _cache[*set].LRU_b &= ~(1 << 0); // clear bit 0
            _cache[*set].LRU_b &= ~(1 << 1); // clear bit 1
            _cache[*set].LRU_b &= ~(1 << 3); // clear bit 3
            break;
        case 1:  // way 1
            _cache[*set].LRU_b &= ~(1 << 0); // clear bit 0
            _cache[*set].LRU_b &= ~(1 << 1); // clear bit 1
            _cache[*set].LRU_b |=  (1 << 3); // set   bit 3
            break;
        case 2:  // way 2
            _cache[*set].LRU_b &= ~(1 << 0); // clear bit 0
            _cache[*set].LRU_b |=  (1 << 1); // set   bit 1
            _cache[*set].LRU_b &= ~(1 << 4); // clear bit 4
            break;
        case 3:  // way 3
            _cache[*set].LRU_b &= ~(1 << 0); // clear bit 0
            _cache[*set].LRU_b |=  (1 << 1); // set   bit 1
            _cache[*set].LRU_b |=  (1 << 4); // set   bit 4
            break;
        case 4:  // way 4 
            _cache[*set].LRU_b |=  (1 << 0); // set   bit 0
            _cache[*set].LRU_b &= ~(1 << 2); // clear bit 2
            _cache[*set].LRU_b &= ~(1 << 5); // clear bit 5
            break;
        case 5:  // way 5
            _cache[*set].LRU_b |=  (1 << 0); // set   bit 0
            _cache[*set].LRU_b &= ~(1 << 2); // clear bit 2
            _cache[*set].LRU_b |=  (1 << 5); // set   bit 5
            break;
        case 6:  // way 6
            _cache[*set].LRU_b |=  (1 << 0); // set   bit 0
            _cache[*set].LRU_b |=  (1 << 2); // set   bit 2
            _cache[*set].LRU_b &= ~(1 << 6); // clear bit 6
            break;
        case 7:  // way 7
            _cache[*set].LRU_b |=  (1 << 0); // set   bit 0
            _cache[*set].LRU_b |=  (1 << 2); // set   bit 2
            _cache[*set].LRU_b |=  (1 << 6); // set   bit 6
            break;
    }
}

