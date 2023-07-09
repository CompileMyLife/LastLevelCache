#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <unistd.h>

#include "parse.h"

// n-mode
int mode = 0;

// address vars
uint32_t addr = 0x0;

// Set and Tag
uint16_t tag = 0;
uint16_t set = 0;

int main(int argc, char *argv[]) {
    // Store option from CLI
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

    // DEBUG
    //printf("Normal Mode = %d, Silent Mode = %d, File Flag = %d, optind = %d\n", 
    //       normal, silent, file_flg, optind);

    if(optind > argc){
        fprintf(stderr, "Expected argument after options\n");
        exit(EXIT_FAILURE);
    }

    // DEBUG
    //printf("file argument = %s\n", file_name);
    
    if (file_flg) {
        FILE *fp = fopen(file_name, "r");
        if (fp == NULL) {
            perror("ERROR: fopen() couldn't open file");
            exit(EXIT_FAILURE);
        }

        // Read each line of the test file with the following format until EOF.
        // Then store the mode and address to respective variable.
        while(fscanf(fp , "%d %x\n", &mode, &addr) != EOF) {
            // LLC program
            if (normal || silent) {
                address_parse(addr, &set, &tag);
            }
            // DEBUG
            printf("mode: %d, address: %X, set: %X, tag: %X\n", mode, addr, set, tag); 
        }
        fclose(fp);

        exit(EXIT_SUCCESS);
    }

    else {
        fprintf(stderr, "ERROR: file_flg was not set\n");
        exit(EXIT_FAILURE);
    }
    
    return 0;
}
