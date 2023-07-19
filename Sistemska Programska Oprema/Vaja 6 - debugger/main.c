#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/user.h>
#include <sys/personality.h>
#include <stdint.h>
#include <errno.h>
#include <string.h>

#define BREAKPOINT 0xCC
#define ENTER 10

unsigned long breakpoint_address = 0;
long original_data = 0;

void set_breakpoint(pid_t child, unsigned long address) {

    printf("Setting breakpoint at 0x%lx\n", address);

    breakpoint_address = address;
    original_data = ptrace(PTRACE_PEEKTEXT, child, (void *)breakpoint_address, NULL);
    long data_with_breakpoint = (original_data & 0xFFFFFFFFFFFFFF00) | BREAKPOINT;
    ptrace(PTRACE_POKETEXT, child, (void *)breakpoint_address, (void *)data_with_breakpoint);
}

void clear_breakpoint(pid_t child, unsigned long address) {

    printf("Clearing breakpoint at 0x%lx\n", address);

    ptrace(PTRACE_POKETEXT, child, (void *)address, (void *)original_data);
    breakpoint_address = 0;
}

void handle_command(pid_t child, const char *command) {
    char cmd[16];
    unsigned long address;
    sscanf(command, "%s %lx", cmd, &address);

    printf("Command: %s\n", cmd);

    struct user_regs_struct regs;
    ptrace(PTRACE_GETREGS, child, NULL, &regs);

    if (strcmp(cmd, "b") == 0) {
        set_breakpoint(child, address);
    } else if (strcmp(cmd, "bs") == 0) {
        set_breakpoint(child, address);
        regs.eip = address;
        ptrace(PTRACE_SETREGS, child, NULL, &regs);
    } else if (strcmp(cmd, "br") == 0) {
        if (breakpoint_address != 0) {
            clear_breakpoint(child, breakpoint_address);
        }
    } else if (strcmp(cmd, "s") == 0) {
        ptrace(PTRACE_SINGLESTEP, child, NULL, NULL);
    } else if (strcmp(cmd, "c") == 0) {
        if (breakpoint_address != 0) {
            clear_breakpoint(child, breakpoint_address);
            regs.eip--;
            ptrace(PTRACE_SETREGS, child, NULL, &regs);
            ptrace(PTRACE_CONT, child, NULL, NULL);
            wait(NULL);
            set_breakpoint(child, breakpoint_address);
        } else {
            ptrace(PTRACE_CONT, child, NULL, NULL);
        }
    } else if (strcmp(cmd, "p") == 0) {
        long value = ptrace(PTRACE_PEEKTEXT, child, (void *)address, NULL);
        if (errno) {
            perror("ptrace");
        } else {
            printf("0x%lx: 0x%lx\n", address, value);
        }
    } else {
        fprintf(stderr, "Neveljaven ukaz: %s\n", command);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Uporaba: %s ime_programa\n", argv[0]);
        return 1;
    }

    pid_t child = fork();

    if (child == 0) {
        personality(ADDR_NO_RANDOMIZE);
        ptrace(PTRACE_TRACEME, 0, NULL, NULL);
        execl(argv[1], argv[1], NULL);
    } else {
        int status;
        waitpid(child, &status, 0);
        while (WIFSTOPPED(status)) {
            char command[32];
            fgets(command, sizeof(command), stdin);
            command[strcspn(command, "\n")] = '\0';
            handle_command(child, command);
            ptrace(PTRACE_SINGLESTEP, child, NULL, NULL);
            waitpid(child, &status, 0);
        }
    }

    return 0;
}