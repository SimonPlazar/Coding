#include <stdio.h>

int
main()
{
	printf("Child> Begin\n");

	asm("    pushl %ebx        \n"    // Dodaj vrednost registra ebx na sklad.
		"    movl  $143, %ebx  \n"    // Nastavi register ebx na vrednost 143.
		"L1: cmpl  $245, %ebx  \n"    // Primerjaj vrednost 245 z vrednostjo registra ebx.
		"    jne   L1          \n"    // Ce sta vrednosti razlicni, skoci na oznako L1.
		"    popl  %ebx        \n");  // Odstrani vrednost iz sklada in jo shrani v register ebx.

	// Zanka se izvaja dokler ebx nima vrednosti 245

	printf("Child> End\n");

	return 0;
}
