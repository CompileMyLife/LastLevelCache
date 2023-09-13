#include "parse.h"

// Parse the address bits for the tag, byte select, and set bits
//
// NOTE: 
// The address is 32 bits, the tag is 11 bits [32:21], index/set is 
// 15 bits [20:6], and the byte select is 6 bits [5:0]
void address_parse(uint32_t* address, uint16_t* _set, uint16_t* _tag, uint8_t* _byte_sel) {
    // set to 0 initially
    *_tag      = 0;
    *_set      = 0;
    *_byte_sel = 0;

    // Tag bits are [32:21]
    *_tag = (*address & 0xFFE00000) >> 21;

    // Set bits are [20:6]
    *_set = (*address & 0x1FFFC0) >> 6;

    // Byte Select bits are [5:0]
    *_byte_sel = (*address & 0x0000003F);
}
