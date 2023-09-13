#include "snoop.h"

// Bus Operation types
// READ=1, WRITE=2, INVALIDATE=3, RWIM=4
//
// Simulate a bus operation and to capture the snoop results of last level
// caches of other processors
void operate_bus(char* op, uint32_t* address) {
    snoop_results result = get_snoop_result(address);

    if (normal) {
        switch (result) {
            case NOHIT:
                fprintf(stdout, "Bus Operation: %s, Address: %08X, Snoop Result: NOHIT\n", 
                    op, *address);
                break;
            case HITM:
                fprintf(stdout, "Bus Operation: %s, Address: %08X, Snoop Result: HITM\n", 
                    op, *address);
                break;
            case HIT:
            default:
                fprintf(stdout, "Bus Operation: %s, Address: %08X, Snoop Result: HIT\n", 
                    op, *address);
                break;
        }
    }
}

// Simulate the report of snoop results by other caches
// Returns the snoop result from address
snoop_results get_snoop_result(uint32_t* address) {
    *address = (*address  & 0x00000003); // mask the 1th and 0th bit 

    switch(*address) {
        case 1: 
            return NOHIT;
        case 2:
            return HITM;
        case 0:
        default:
            return HIT;
    }
}

// Report the resutls of the snooping bus operations produced by other caches
void put_snoop_result(uint32_t* address, snoop_results result) {
    if (normal) {
        switch (result) {
            case NOHIT:
                fprintf(stdout, "Snoop Result Address: %08X, Snoop Result: NOHIT\n", *address);
                break;
            case HITM:
                fprintf(stdout, "Snoop Result Address: %08X, Snoop Result: HITM\n", *address);
                break;
            case HIT:
            default:
                fprintf(stdout, "Snoop Result Address: %08X, Snoop Result: HIT\n", *address);
                break;
        }
    }
}

// L2 to L1 message types
// GETLINE=1, SENDLINE=2, INVALIDATELINE=3, EVICTLINE=4
//
// Simulate communication to higher level cache
void msg_to_cache(char* msg, uint32_t* address) {
    if (normal) {
        fprintf(stdout, "L2 Cache: %s %08X\n", msg, *address);
    }
}
