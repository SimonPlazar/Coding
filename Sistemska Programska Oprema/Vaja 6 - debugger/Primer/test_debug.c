#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ptrace.h>
#include <unistd.h>

int var_1 = 50;
int var_2 = 100;

int main()
{
	printf("Child> Begin\n");

	// Ponavljaj zanko dokler spremenljivka v ni enaka 245
	while (var_1 != 245)
	{
		printf("Child> Loop 1 - value of var_1: %d\n", var_1);
		var_1 = var_1 + 1;

		sleep(1);
	}

	printf("Child> One\n");
	printf("Child> Two\n");
	printf("Child> Three\n");
	printf("Child> Four\n");
	printf("Child> Five\n");
	printf("Child> Six\n");
	printf("Child> Seven\n");
	printf("Child> Eight\n");
	printf("Child> Nine\n");
	printf("Child> Ten\n");

    // Ponavljaj zanko dokler spremenljivka v ni enaka 0
    while (var_2 != 0)
	{
		printf("Child> Loop 2 - value of var_2: %d\n", var_2);
		var_2 = var_2 - 1;

		sleep(1);
	}

	printf("Child> End\n");

	return 0;
}