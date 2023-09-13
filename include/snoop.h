#ifndef __SNOOP_H
#define __SNOOP_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

// Global bool flags from main.c
extern bool normal;
extern bool silent;

// Bus Operation types
// READ=1, WRITE=2, INVALIDATE=3, RWIM=4

// Snoop Result types
typedef enum _snoop_results{NOHIT, HIT, HITM} snoop_results;

// L2 to L1 message types
// GETLINE=1, SENDLINE=2, INVALIDATELINE=3, EVICTLINE=4

// Simulate a bus operation and to capture the snoop results of last level
// caches of other processors
void operate_bus(char* op, uint32_t* address);

// Simulate the report of snoop results by other caches
// Returns the snoop result from address
snoop_results get_snoop_result(uint32_t* address);

// Report the resutls of the snooping bus operations produced by other caches
void put_snoop_result(uint32_t* address, snoop_results result);

// Simulate communication to higher level cache
void msg_to_cache(char* msg, uint32_t* address);

#endif
