#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <unistd.h>

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

    // Debug
    printf("Normal Mode = %d, Silent Mode = %d, File Flag = %d, optind = %d\n", 
            normal, silent, file_flg, optind);

    if(optind > argc){
        fprintf(stderr, "Expected argument after options\n");
        exit(EXIT_FAILURE);
    }

    // Debug
    printf("file argument = %s\n", file_name);

    // LLC program
    if (normal || silent) {
        // Address Parse
    }

    exit(EXIT_SUCCESS);

}
