#include <stdio.h>
#include <unistd.h>

int v_var = 1;

int main()
{
	printf("Child> Begin\n");

	// Izpisi naslov spremenljivke v
	printf("Child> Address of variable v_var: %p\n", &v_var);

	// Ponavljaj zanko dokler spremenljivka v ni enaka 245
	while (v_var != 245)
	{
		printf("Child> Value of v_var: %d\n", v_var);
		v_var = v_var + 1;

		sleep(1);
	}

	printf("Child> End\n");

	return 0;
}
