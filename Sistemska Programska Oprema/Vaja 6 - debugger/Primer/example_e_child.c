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

	printf("Child> End\n");

	return 0;
}
