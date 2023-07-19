#include <sys/types.h> //libc6-dev-i386
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <syscall.h>

int main(void)
{
    // Sistemski klic je vmesnik (interface) med aplikacijo v uporabniškem prostoru in storitvijo, ki jo nudi jedro.
    // Ker je storitev zagotovljena znotjar jedra, direktni klic ni mogoč.
    // Zato moramo uporabiti postopek, s katerim preidemo mejo med uporabniškim prostorom in jedrom

    // Postopek se razlikuje glede na arhitekturo, zato se bomo trenutno omejili na x86-32.

    // Sistemski skic se jedru pošlje preko ene vstopne točke
    // Postopek začnemo z zapisom številke sistemskega klica v register eax
    // Nadaljujemo z vzbujanjem programske prekinitve (interrupt 0x80)

    // Poglejmo nekaj primerov

    // Pridobimo PID na različne načine 
    int pid = 0;
    int eax_pid = 0;

    pid = (int) getpid(); // Z uporabo C-knjižnice - wrapped
    printf("PID procesa (getpid): %d\n", pid); 

    pid = syscall(SYS_getpid); // Z uporabo direktnega sistemskega klica
    printf("PID procesa (syscall): %d\n", pid); 

    // Z uporabo inline ASM kode
    __asm__ __volatile__ (       
            "movl $0x14, %%eax;" // Zapis številke sistemskega klica          	
            "int  $0x80;"        // Klic jedra          	
            : "=r"(eax_pid)      // Rezultat iz registra eax     	        	
    );
    printf("PID procesa (asm): %d\n", eax_pid); 

    return 0;

    // Seznam sistemskih klicev:
    //  - https://chromium.googlesource.com/chromiumos/docs/+/master/constants/syscalls.md#x86-32_bit
}       
