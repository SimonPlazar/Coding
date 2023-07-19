#include "misc.h"

#include <stdio.h>
#include <stdlib.h>

void check_ptrace(long result)
{
	if (result == -1) {
		perror("ptrace");
		exit(-1);
	}
}

void check_execve(int result)
{
	if (result == -1) {
		perror("execve");
		exit(-1);
	}
}

void check_waitpid_status(int wstatus)
{
	if (WIFSTOPPED(wstatus)) {
		printf("Child> Stop\n");
	}

	if (WIFEXITED(wstatus)) {
		printf("Child> Exit\n");
	}
}
