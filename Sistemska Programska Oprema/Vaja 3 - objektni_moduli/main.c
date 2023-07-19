
#include <unistd.h> 
#include <getopt.h>
#include <stdbool.h>

#include "elf_loader.h"

int main(int argc, char *argv[])
{
    bool FLAG_H = false;
    bool FLAG_S = false;
    bool FLAG_L = false;
    bool FLAG_R = false;

    int opt;

    while((opt = getopt(argc, argv, ":hSlr")) != -1) 
    { 
        switch(opt) 
        { 
            case 'h':
                FLAG_H = true;
                break;
            case 'S':
                FLAG_S = true;
                break;
            case 'l':
                FLAG_L = true;
                break;
            case 'r':
                FLAG_R = true;
                break;
            case ':': 
                printf("option needs a value\n"); 
                return 1;
            case '?': 
                printf("unknown option: %c\n", optopt);
                return 1;
        } 
    }

    char *directory;
    if (optind < argc) {
        directory = argv[optind];
    } else {
        printf("No directory specified\n");
        return 1;
    }

    if(FLAG_H)
    {
        read_elf_header(directory);
    }

    if(FLAG_S)
    {
        read_elf_sections(directory);
    }

    if(FLAG_L)
    {
        read_elf_segment_info(directory);
    }

    if(FLAG_R)
    {
        execute_elf(directory);
    }
    
    return 0;
}