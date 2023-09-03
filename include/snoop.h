#ifndef __SNOOP_H
#define __SNOOP_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

extern bool normal;
extern bool silent;

// Bus Operation types
//typedef enum _bus_ops{READ=1, WRITE, INVALIDATE, RWIM} bus_ops;

// Snoop Result types
typedef enum _snoop_results{NOHIT, HIT, HITM} snoop_results;

// L2 to L1 message types
//typedef enum _L2_to_L1_msg{GETLINE=1, SENDLINE, INVALIDATELINE, EVICTLINE} L2_to_L1_msg;

// Simulate a bus operation and to capture the snoop results of last level
// caches of other processors
void operate_bus(char* op, uint32_t* address);

// Simulate the report of snoop results by other caches
snoop_results get_snoop_result(uint32_t* address);

// Report the resutls of the snooping bus operations produced by other caches
void put_snoop_result(uint32_t* address, snoop_results result);

// Simulate communication to higher level cache
void msg_to_cache(char* msg, uint32_t* address);

#endif
