#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 
#include <unistd.h>

#include "parse.h"
#include "cache.h"
#include "ops.h"

#define DEBUG 0

// Globally declared for other includes to use
bool normal = 1, silent = 0;


int main(int argc, char *argv[]) { // Store option from CLI
    int opt;

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

#if (DEBUG)
    printf("file argument = %s\n", file_name);
#endif
    
    if (file_flg) {
        // Create Cache_Stats
        Cache_Stats cache_stats;

        // Create Cache w/ 32768 sets 2^15 sets
        Set* Cache = create_cache();

        // Initialize the cache to specified state and statistics to 0s
        init_cache(Cache, &cache_stats);
        
        // n-mode and address
        uint8_t mode = 0;
        uint32_t addr = 0;

        FILE *fp = fopen(file_name, "r");
        if (fp == NULL) {
            perror("ERROR: fopen() couldn't open file");
            exit(EXIT_FAILURE);
        }

        // Read each line of the test file with the following format until EOF.
        // Then store the mode and address to respective variable.
        while(fscanf(fp, "%hhu %x\n", &mode, &addr) != EOF) {
            // LLC program
            address_parse(&addr, &set, &tag, &byte_sel);
            
            switch(mode) {
                case 0:
                    mode_0(Cache, &cache_stats, &addr, &tag, &set);
                    break;
                case 1:
                    mode_1(Cache, &cache_stats, &addr, &tag, &set);
                    break;
                case 2:
                    mode_2(Cache, &cache_stats, &addr, &tag, &set);
                    break;
                case 3:
                    mode_3(Cache, &cache_stats, &addr, &tag, &set);
                    break;
                case 4:
                    mode_4(Cache, &cache_stats, &addr, &tag, &set);
                    break;
                case 5:
                    mode_5(Cache, &cache_stats, &addr, &tag, &set);
                    break;
                case 6:
                    mode_6(Cache, &cache_stats, &addr, &tag, &set);
                    break;
                case 8:
                    mode_8(Cache);
                    break;
                case 9:
                    mode_9(Cache);
                    break;
                default:
                    fprintf(stderr, "ERROR: Invalid parsed command\n");
            }
#if (DEBUG)
            printf("mode: %hhu, address: %X, tag: %X, index: %X, byte sel.: %X\n", mode, addr, tag, set, byte_sel); 
#endif
        }
        fclose(fp);

        cache_stats.hit_ratio = (double) cache_stats.hits / (double) (cache_stats.reads + cache_stats.writes);
        cache_stats.miss_ratio = (double) cache_stats.misses / (double) (cache_stats.reads + cache_stats.writes);
        
        fprintf(stdout, "Total Memory Accesses = %ld, Reads = %ld, Writes = %ld, HITs = %ld, MISSes = %ld, Hit Ratio = %f, Miss Ratio = %f\n", cache_stats.reads + cache_stats.writes, cache_stats.reads, cache_stats.writes, cache_stats.hits, cache_stats.misses, cache_stats.hit_ratio, cache_stats.miss_ratio);

        delete_cache(Cache);

        exit(EXIT_SUCCESS);
    }

    else {
        fprintf(stderr, "ERROR: file_flg was not set\n");
        exit(EXIT_FAILURE);
    }
    
    return 0;
}
