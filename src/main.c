#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 
#include <unistd.h>

#include "parse.h"
#include "cache.h"

#define DEBUG 0

// n-mode
int mode = 0;

// address vars
uint32_t addr = 0x0;

// Set and Tag
uint16_t tag = 0;
uint16_t set = 0;

int main(int argc, char *argv[]) { // Store option from CLI
    int opt;

    // Flags; by default running in Normal Mode
    bool normal = 1, silent = 0;
    bool file_flg = 0;

    char* file_name = NULL;

    while ((opt = getopt(argc, argv, "sf:")) != -1) {
        switch (opt) {
            case 's':
                silent = 1;
                normal = 0;
                break;
            case 'f':
                file_name = optarg;
                file_flg = 1;
                break;
            default:
                fprintf(stderr, "Usage: %s [-s] [-f] <path/to/file>\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

#if (DEBUG)
    printf("Normal Mode = %d, Silent Mode = %d, File Flag = %d, optind = %d\n", 
           normal, silent, file_flg, optind);
#endif

    if(optind > argc){
        fprintf(stderr, "Expected argument after options\n");
        exit(EXIT_FAILURE);
    }

    // DEBUG
#if (DEBUG)
    printf("file argument = %s\n", file_name);
#endif
    
    if (file_flg) {
        Cache_Stats cache_stats;

        // Create Cache w/ 32768 sets 2^15 sets
        Set* Cache = create_cache();

        // Initialize the cache to specified state and statistics to 0s
        init_cache(Cache, &cache_stats);

        FILE *fp = fopen(file_name, "r");
        if (fp == NULL) {
            perror("ERROR: fopen() couldn't open file");
            exit(EXIT_FAILURE);
        }

        // Read each line of the test file with the following format until EOF.
        // Then store the mode and address to respective variable.
        while(fscanf(fp, "%d %x\n", &mode, &addr) != EOF) {
            // LLC program
            if (normal || silent) {
                address_parse(&addr, &set, &tag);
            }

#if (DEBUG)
            printf("mode: %d, address: %X, set: %X, tag: %X\n", mode, addr, set, tag); 
#endif
        }
        fclose(fp);

        for (int i = 0; i < 32768; i++){
            for(int j = 0; j < 8; j++){
                printf("Cache[%d].tag[%d] = %X\n", i, j, Cache[i].tag[j]);
            }
        }

        delete_cache(Cache);

        exit(EXIT_SUCCESS);
    }

    else {
        fprintf(stderr, "ERROR: file_flg was not set\n");
        exit(EXIT_FAILURE);
    }
    
    return 0;
}
