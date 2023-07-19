#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/ptrace.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	// Omogoci, da bo trenutnemu procesu lahko sledil stars
	long r = ptrace(PTRACE_TRACEME, 0, NULL, NULL);

	if (r == -1) {
		perror("ptrace");
		exit(-1);
	}

	// Stevec, ki pristeva vrednosti in jih izpisuje
	uint32_t cnt = 0;

	while (true)
	{
		printf("Child> Counter: %d\n", cnt++);
		sleep(1);
	}

	return 0;
}
