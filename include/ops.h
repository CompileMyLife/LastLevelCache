#ifndef __OPS_H
#define __OPS_H

#include <stdint.h>

#include "cache.h"
#include "PLRU.h"

void mode_0(Set* _cache, Cache_Stats* _cache_stats, uint16_t* tag, uint16_t* set, uint8_t* byte_sel);

void mode_1(Set* _cache, Cache_Stats* _cache_stats, uint16_t* tag, uint16_t* set, uint8_t* byte_sel);

void mode_2(Set* _cache, Cache_Stats* _cache_stats, uint16_t* tag, uint16_t* set, uint8_t* byte_sel);

void mode_3(Set* _cache, Cache_Stats* _cache_stats, uint16_t* tag, uint16_t* set, uint8_t* byte_sel);

void mode_4(Set* _cache, Cache_Stats* _cache_stats, uint16_t* tag, uint16_t* set, uint8_t* byte_sel);

void mode_5(Set* _cache, Cache_Stats* _cache_stats, uint16_t* tag, uint16_t* set, uint8_t* byte_sel);

void mode_6(Set* _cache, Cache_Stats* _cache_stats, uint16_t* tag, uint16_t* set, uint8_t* byte_sel);

void mode_8(Set* _cache, Cache_Stats* _cache_stats);

void mode_9(Set* _cache);

#endif
