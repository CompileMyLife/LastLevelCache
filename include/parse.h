#ifndef __PARSE_H
#define __PARSE_H

#include <stdint.h>

uint32_t addr;

uint16_t tag;
uint16_t set;
uint8_t byte_sel;

// Parse the address bits for the tag, byte select, and set bits
//
// NOTE: 
// The address is 32 bits, the tag is 11 bits [32:21], index/set is 
// 15 bits [20:6], and the byte select is 6 bits [5:0]
void address_parse(uint32_t* address, uint16_t* _set, uint16_t* _tag, uint8_t* _byte_sel);

#endif
