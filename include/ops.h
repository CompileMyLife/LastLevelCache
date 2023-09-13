#ifndef __OPS_H
#define __OPS_H

#include <stdint.h>

#include "cache.h"
#include "PLRU.h"
#include "snoop.h"

// Global bool flags from main.c
extern bool normal;
extern bool silent;

// Read request from L1 data cache
void mode_0(Set* _cache, Cache_Stats* _cache_stats, uint32_t* addr, uint16_t* tag, uint16_t* set);

// Write request form L1 data cache
void mode_1(Set* _cache, Cache_Stats* _cache_stats, uint32_t* addr, uint16_t* tag, uint16_t* set);

// Read request from L1 instruction cache
void mode_2(Set* _cache, Cache_Stats* _cache_stats, uint32_t* addr, uint16_t* tag, uint16_t* set);

// Snooped invalidate command
void mode_3(Set* _cache, Cache_Stats* _cache_stats, uint32_t* addr, uint16_t* tag, uint16_t* set);

// Snooped read request
void mode_4(Set* _cache, Cache_Stats* _cache_stats, uint32_t* addr, uint16_t* tag, uint16_t* set);

// Snooped write request
void mode_5(Set* _cache, Cache_Stats* _cache_stats, uint32_t* addr, uint16_t* tag, uint16_t* set);

// Snooped read with intent to modify request
void mode_6(Set* _cache, Cache_Stats* _cache_stats, uint32_t* addr, uint16_t* tag, uint16_t* set);

// Clear the cache and reset all state
void mode_8(Set* _cache);

// Print the contents and state of each valid cache line
void mode_9(Set* _cache);

#endif
