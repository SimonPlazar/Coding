#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <syscall.h>

const char* output = "Zdravo!\n";

int main(void)
{
    // Uporaba rip na 64-bitni arhitekturi - relativno naslavljanja

    // Z uporabo inline ASM kode
    __asm__ __volatile__ (           
            "movq   $0x01,  %rax;" 
            "movq   $0x01,  %rdi;"
            "movq   output(%rip), %rsi;" 
            "movq   $8,     %rdx;"  	
            "syscall;"     	        	
    );

    return 0;         
}       
