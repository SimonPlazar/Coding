#include <sys/types.h> //libc6-dev-i386
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <syscall.h>
#include <fcntl.h>

int main(void)
{
    // Sistemski klic s parametri
    // Parametre sistemskega klica nastavimo preko splošno namenskih registrov
    // ebx, ecx, edx, esi, edi, ebp

    // Izpišimo navodilo uporabniku
    // write(1, output, 10);

    const char* output_name_1 = "Vnesi:";
    __asm__ __volatile__ (     
          "movl $0x01,  %%ebx;"   // Standardni izhod - oprimek 1 
          "movl %[out], %%ecx;"   // Kazalec na vsebino za izpis 
          "movl $0x07,  %%edx;"   // Dolžina izpisa
          "movl $0x04,  %%eax;"   // Sistemski klic write    
          "int  $0x80;"           // Klic jedra    
        : 
        : [out]"r"(output_name_1) 
        : "%eax", "%ebx", "%ecx", "%edx"
    );

    // Kako poiščemo kaj pomenijo parametri?
    // Več o tem: https://man7.org/linux/man-pages/man2/write.2.html

    // Preberemo vnos
    // read(2, input_name, 10);

    char input_name[10];  
    __asm__ __volatile__ (     
          "movl $0x02,  %%ebx;"  // Standardni vhod - oprimek 2
          "movl %[in],  %%ecx;"  // Kazalec na spremenljivko 
          "movl $0x10,  %%edx;"  // Dolžina    
          "movl $0x03,  %%eax;"  // Sistemski klic read 
          "int  $0x80;"          // Klic jedra    
          : 
          : [in]"r"(input_name) 
          : "%eax", "%ebx", "%ecx", "%edx"
    );

	// Izpišimo skupaj
    // write(1, output_name_2, 7);
    // write(1, input_name, 10);

    const char* output_name_2 = "Izpis:";
    __asm__ __volatile__ (     
          "movl $0x01,  %%ebx;"   // Standardni izhod - oprimek 1 
          "movl %[out], %%ecx;"   // Kazalec na vsebino za izpis 
          "movl $0x07,  %%edx;"   // Dolžina izpisa
          "movl $0x04,  %%eax;"   // Sistemski klic write    
          "int  $0x80;"           // Klic jedra    
        : 
        : [out]"r"(output_name_2) 
        : "%eax", "%ebx", "%ecx", "%edx"
    );

    __asm__ __volatile__ (     
          "movl $0x01,  %%ebx;"   // Standardni izhod - oprimek 1 
          "movl %[out], %%ecx;"   // Kazalec na vsebino za izpis 
          "movl $0x10,  %%edx;"   // Dolžina izpisa
          "movl $0x04,  %%eax;"   // Sistemski klic write    
          "int  $0x80;"           // Klic jedra    
        : 
        : [out]"r"(input_name) 
        : "%eax", "%ebx", "%ecx", "%edx"
    );

}       
