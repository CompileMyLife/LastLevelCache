#include "parse.h"

void address_parse(uint32_t address, uint16_t *set, uint16_t *tag) {
    // set to 0 initially
    *tag = 0;
    *set = 0;

    // Tag bits are [32:21]
    *tag = (address & 0xFFE00000) >> 21;

    // Set bits are [20:6]
    *set = (address & 0x1FFFC0) >> 6;

    // DEBUG:
}
