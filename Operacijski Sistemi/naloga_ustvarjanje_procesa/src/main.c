#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <getopt.h>
#include <string.h>
#include <fcntl.h>

#include "pipeline.h"
#include "read_commands.h"


void debug_print_cmd_list(char*** command_list) {
    printf("\n");
    printf("content:\n");

    int cmd_ind = 0;
    for (char*** cmd = command_list; cmd[0] != 0; cmd += 1) {
        printf("command %d (%p):\n", cmd_ind, cmd);
        cmd_ind = cmd_ind+1;
        int arg_ind = 0;
        for (char** arg = cmd[0]; *arg != 0; arg += 1) {
            printf("argument %d (%p): %s\n", arg_ind, arg, *arg);
            arg_ind += 1;
        }
    }
}

int main(int argc, char** argv) {
    static struct option long_options[] = {
        {"help",   no_argument,       0, (int)'h'},
        {"input",  required_argument, 0, (int)'i'},
        {"output", required_argument, 0, (int)'o'},
        {"script", required_argument, 0, (int)'s'},
        {"error", required_argument, 0, (int)'e'},
        {       0,                 0, 0,        0},
    };

    int script_input    = 0;
    int pipeline_input  = -1;
    int pipeline_output = 1;
    int pipeline_error = 2;

    while (true) {
        int c = getopt_long(argc, argv, ":hi:o:e:s:", long_options, 0);
        if (c == -1) {
            break;
        }

        switch (c) {
            case 'h': {
                printf("usage: %s [OPTION]\n", argv[0]);
                printf("read pipeline from input file\n");
                printf("or standard input if no file is given\n");
                printf(" -i <file>\n");
                printf("use as input file for the pipeline\n");
                printf(" -o <file>\n");
                printf("use as output file for the pipeline, will be created or truncated\n");
                printf(" -e <file>\n");
                printf("use as standard error output for pipeline\n");
                printf(" -s <file>\n");
                printf("read pipeline commands from the given file\n");
                printf("\n");
                exit(0);
            }
            case 'i': {
                pipeline_input = open(optarg, O_RDONLY);
                break;
            }
            case 'o': {
                pipeline_output = open(optarg, O_WRONLY|O_CREAT|O_TRUNC, 0660);
                break;
            }
            case 's': {
                script_input = open(optarg, O_RDONLY);
                break;
            }
            case 'e': {
                pipeline_error = open(optarg, O_WRONLY|O_CREAT|O_TRUNC, 0660);
                break;
            }
            case '?': {
                printf("error ?\n");
                exit(EXIT_FAILURE);
            }
            case ':': {
                printf("error :\n");
                exit(EXIT_FAILURE);
            }
        }
    }

    char*** cmd_list = read_command_list(script_input);

    int r = execute_pipeline(cmd_list, pipeline_input, pipeline_output, pipeline_error);
    free(cmd_list);

    return r;
}
