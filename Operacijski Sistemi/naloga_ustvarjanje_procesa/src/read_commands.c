#include <stddef.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

void data_dump(unsigned char* data, int len) {
    // byte by byte print
    printf("hex data:\n");
    for (int i = 0; i < len; i += 8) {
        printf("%p ", &data[i]);
        for (int j = 0; j < 8 && j+i < len; j += 1) {
            printf("%.2x", data[i+j]);
        }
        printf("\n");
    }
}

char* read_command_str(int input_fd) {
    size_t com_buf_len = 10;
    size_t com_len     = 1;
    char*  command_str = malloc(com_buf_len);
    command_str[0] = '\n'; // extra new line, just in case input is empty
    while (true) {
        ssize_t r = read(input_fd, command_str+com_len, com_buf_len-com_len-1);
        if (r == 0) {
            break;
        }
        if (r == -1) {
            perror("error while reading commands");
            break;
        }
        com_len += r;
        if (com_len == com_buf_len-1) {
            com_buf_len *= 2;
            command_str  = realloc(command_str, com_buf_len*sizeof(char));
        }
    }
    if (command_str[com_len-1] != '\n') {
        command_str[com_len] = '\n'; // if the commands don't end with a newline add one
        com_len += 1;
    }
    // if buffer is full, add one more space for zero termination
    if (com_len == com_buf_len) {
        com_buf_len += 1;
        command_str  = realloc(command_str, com_buf_len*sizeof(char));
    }
    command_str[com_len] = 0;
    return command_str;
}

char*** proc_cmd_str(char* cmd_str) {
    // first count the total number of commands and arguments
    int    cmd_count   = 1; // need to 0 terminate the commands
    int    arg_count   = 0;
    size_t cmd_str_len = strlen(cmd_str);

    char* arg_start     = cmd_str;
    int   arg_cmd_count = 0;
    for (char* c = cmd_str; c[0] != 0; c += 1) {
        if (c[0] == ' ') {
            // non empty argument?
            if (c-arg_start > 0) {
                arg_cmd_count += 1;
            }
            arg_start = c+1;
        } else
        if (c[0] == '\n') {
            // non empty argument?
            if (c-arg_start > 0) {
                arg_cmd_count += 1;
            }
            // line with arguments?
            if (arg_cmd_count > 0) {
                cmd_count += 1;
                // each command needs 1 extra argument spot for 0 termination
                arg_cmd_count += 1;
                arg_count     += arg_cmd_count;
                arg_cmd_count  = 0;
            }
            arg_start = c+1;
        }
    }

    // prepare the necessary space and break down the commands
    size_t data_size = sizeof(char**)*cmd_count
                       +sizeof(char*)*arg_count
                       +cmd_str_len*sizeof(char)+1;
    char*** cmd_list = malloc(data_size);
    memset(cmd_list, 0, data_size);

    char** args_list    = (char**)&cmd_list[cmd_count];
    char*  cmd_str_proc = (char*)&args_list[arg_count];

    strncpy(cmd_str_proc, cmd_str, cmd_str_len+1);

    int   cmd_ind   = 0;            // the current command
    int   arg_first = 0;            // first argument of the current command
    int   arg_ind   = 0;            // the current argument
    char* c_first   = cmd_str_proc; // first character of the current argument
    for (char* c = cmd_str_proc; c[0] != 0; c += 1) {
        if (c[0] == ' ') {
            c[0] = 0;
            if (strlen(c_first) > 0) { // new non-empty argument
                args_list[arg_ind] = c_first;
                arg_ind           += 1;
            }
            c_first = c+1;
        }
        if (c[0] == '\n') {
            c[0] = 0;

            if (strlen(c_first) > 0) { // new non-empty argument
                args_list[arg_ind] = c_first;
                arg_ind           += 1;
            }
            c_first = c+1;

            if (arg_first < arg_ind) { // new command with non-empty argument list
                cmd_list[cmd_ind] = &args_list[arg_first];
                cmd_ind          += 1;
                arg_ind          += 1; // zero terminate the list of arguments for this command
            }
            arg_first = arg_ind;
        }
    }

    //data_dump((unsigned char*)cmd_list, data_size);

    return cmd_list;
}

char*** read_command_list(int input) {
    char*   command_str = read_command_str(input);
    char*** cmd_list    = proc_cmd_str(command_str);
    free(command_str);

    return cmd_list;
}
