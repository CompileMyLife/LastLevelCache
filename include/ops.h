#ifndef __OPS_H
#define __OPS_H

#include <stdint.h>

#include "cache.h"
#include "PLRU.h"
#include "snoop.h"

extern bool normal;
extern bool silent;

void mode_0(Set* _cache, Cache_Stats* _cache_stats, uint32_t* addr, uint16_t* tag, uint16_t* set);

void mode_1(Set* _cache, Cache_Stats* _cache_stats, uint32_t* addr, uint16_t* tag, uint16_t* set);

void mode_2(Set* _cache, Cache_Stats* _cache_stats, uint32_t* addr, uint16_t* tag, uint16_t* set);

void mode_3(Set* _cache, Cache_Stats* _cache_stats, uint32_t* addr, uint16_t* tag, uint16_t* set);

void mode_4(Set* _cache, Cache_Stats* _cache_stats, uint32_t* addr, uint16_t* tag, uint16_t* set);

void mode_5(Set* _cache, Cache_Stats* _cache_stats, uint32_t* addr, uint16_t* tag, uint16_t* set);

void mode_6(Set* _cache, Cache_Stats* _cache_stats, uint32_t* addr, uint16_t* tag, uint16_t* set);

void mode_8(Set* _cache);

void mode_9(Set* _cache);

#endif
