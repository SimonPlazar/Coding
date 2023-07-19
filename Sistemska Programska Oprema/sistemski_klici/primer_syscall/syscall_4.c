#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <syscall.h>
 
int main(void)
{
    // Kako je s sistemskimi klici na 64-bitni arhitekturi

    // Sistemski klic se izvede s syscall inštrukcijo
    // Registri imajo predpono r (pri x86 je predpona e)
    // Po klicu jedro uniči registra rcx in r11
    // Register rax vsebuje rezultat sistemskega klica

    int pid = 0;

    pid = (int) getpid(); // Z uporabo C-knjižnice - wrapped
    printf("PID procesa (getpid): %d\n", pid); 

    pid = syscall(SYS_getpid); // Z uporabo direktnega sistemskega klica
    printf("PID procesa (syscall): %d\n", pid); 

    // Z uporabo inline ASM kode
    __asm__ __volatile__ (           
            "movq   $0x27, %%rax \n" 
            "syscall             \n"    	
            :
            "=a"(pid)          	        	
    );
    printf("PID procesa (asm): %d\n", pid); 

    return 0;

    // Seznam sistemskih klicev:
    //  - https://chromium.googlesource.com/chromiumos/docs/+/master/constants/syscalls.md#x86_64-64_bit            
}       
