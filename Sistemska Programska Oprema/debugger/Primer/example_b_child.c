#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ptrace.h>
#include <unistd.h>

int main()
{
	printf("Child> Begin\n");

	// Stevec, ki pristeva vrednosti in jih izpisuje
	uint32_t cnt = 0;
	
	while (cnt <= 10)
	{
		printf("Child> Counter: %d\n", cnt++);
		sleep(1);
	}

	printf("Child> End\n");

	return 0;
}
