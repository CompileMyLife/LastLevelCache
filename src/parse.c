#include "parse.h"

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
