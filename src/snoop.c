#include "snoop.h"

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

void msg_to_cache(char* msg, uint32_t* address) {
    if (normal) {
        fprintf(stdout, "L2 Cache: %s %08X\n", msg, *address);
    }
}
