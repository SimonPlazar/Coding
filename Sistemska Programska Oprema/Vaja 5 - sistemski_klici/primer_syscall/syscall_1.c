#include <sys/types.h> //libc6-dev-i386
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <syscall.h>

int c_var_eax_g = 0;

int main (void)
{                                               
    // Poglejmo nekaj primero uporabe inline asm
    // - https://gcc.gnu.org/onlinedocs/gcc/Extended-Asm.html#Extended-Asm
    
    // Zgradba inline asm
    // asm asm-qualifiers (AssemblerTemplate 
    //                      : OutputOperands // A comma-separated list of the C variables modified by the instructions in the AssemblerTemplate.
    //                      : InputOperands // A comma-separated list of C expressions read by the instructions in the AssemblerTemplate
    //                      : Clobbers // A comma-separated list of registers or other values changed by the AssemblerTemplate
    //                      : GotoLabels) // When you are using the goto form of asm, this section contains the list of all C labels to which the code in the AssemblerTemplate may jump

    /*
        1) Nastavljanje registra in branje vrednosti
    */
    int c_var_eax_l = 0;

    __asm__ __volatile__ (           // __volatile__ modifier prisili prevajalnikov optimizator, da izvede kodo as-is
          "movl $0x05, %eax;"        // V register eax "zapišimo" vrednost 0x05
          "movl %eax, c_var_eax_g;"  // Iz registra "preberimo" vrednost in jo "zapišimo" v spremenljivko c_var_eax_l
    );
    printf("1) Vrednost c_var_eax_l: %d\n", c_var_eax_l);
    printf("1) Vrednost c_var_eax_g: %d\n", c_var_eax_g);

    // Zakaj dobimo napako: undefined reference to `c_var_eax_l'
    // Spremenimo c_var_eax_l v c_var_eax_g

    // Zakaj ozpozorilo pri prevajanju (warning: creating DT_TEXTREL in a PIE)
    // Privzeto je vključeno PIE (position-independent executable)
    // Prevedimo z zastavico -no-pie
    // Onemogočimo izvedbo position-independent executable (PIE), torej onemogočimo address space layout randomization (ASLR)
    // Ne želimo si onemogočat PIE

    /*
        2) Nastavljanje registra ter uporaba C-jevskih spremenljivk
    */
    int c_var_eax = 0;

    __asm__ __volatile__ (             
          "movl $0x05, %%eax;"  // V register eax "zapišimo" vrednost 0x05
          "movl %%eax, %0;"     // Iz registra "preberimo" vrednost in jo "zapišimo" v %0 (kaj predstavlja $0)
        : "=r"(c_var_eax)       // %0 predstavlja C-jevsko spremenvljivko c_var_eax
        :                       // Brez vhodnih operandov
        : "%eax"                // "Čiščenje" registra
    );
    printf("2) Vrednost c_var_eax: %d\n", c_var_eax);

    // Kaj se zgodi če odstranimo drugo vrstico ("branje" vrednosti iz eax)?
    // Poskusimo še odstranit zandjo vrstico ("čiščenje" registra)
    // Kako to, da po odstranitvi v spremenjlivko c_var_eax dobimo željeno vrednost?
    // Privzeto %0 uporabljen za eax register 
    // Prevedimo še s zastavico -S in poglejmo generirano asm kodo.
    // Vidimo lahko, kako %0 prevajalnik nadomesti z registom
    // Kaj se zgodi, če namesto =r zapišemo =m ali pa =rm?

    /*
        3) Seštevanje dveh števil
    */
    int c_var_eax_sum = 0;

    __asm__ __volatile__ (   
          "movl $0x05, %%eax;"          
          "addl $0x05, %%eax;"
        : "=r"(c_var_eax_sum)
    );
    printf("3) Vrednost c_var_eax_sum: %d\n", c_var_eax_sum);

    // Kaj se zgodi, če želimo uporabit asm ukaz "addl $0x05, $0x05;"

    /*
        4) Seštevanje dveh C-jevskih spremenljivk
    */
    int c_var_sum_in_1 = 5;
    int c_var_sum_in_2 = 10;
    int c_var_sum_out = 0;

    __asm__ __volatile__ (   
          "movl %2, %0;"          
          "addl %1, %0;"
        : "=r"(c_var_sum_out)
        : "r"(c_var_sum_in_1), "r"(c_var_sum_in_2)     
    );
    printf("4) Vrednost c_var_sum_out: %d\n", c_var_sum_out);

    // Zakaj nismo dobili pravilnega seštevka?
    // GCC predvideva, da se bodo vhodni vsi vhodni operandi uporabili preden bomo posodobili izhodne operande,
    // kar pomeni, da lahko GCC vhodni in izhodni operand priredi na enak register
    // Kako lahko rešimo napako: vrstico "=r(c_var_sum_out)" spremenimo v "=&r"(c_var_sum_out)
    // Več o tem: https://gcc.gnu.org/onlinedocs/gcc-4.6.2/gcc/Modifiers.html#Modifiers

    /*
        5) Seštevanje C-jevse spremenljivke in vrednosti s pomočjo ecx registra
    */
    c_var_sum_in_1 = 5;
    c_var_sum_out = 0;

    __asm__ __volatile__ (   
          "movl $0x07, %%ecx;"          
          "addl %1,    %%ecx;"
        : "=r"(c_var_sum_out)
        : "r"(c_var_sum_in_1)   
    );
    printf("5) Vrednost c_var_sum_out: %d\n", c_var_sum_out);

    // Zakaj v c_var_sum_out ne dobimo seštevka?
    // Dodajmo vrstico "movl %%ecx, %0;"

    /*
        5) Še zadnji primer manipulacije z ukazom rol in uporabo simboličnih imen
    */
    int c_var_rol = 1;

    __asm__ __volatile__ (   
          "movl $0x08, %%ecx;"          
          "rol  %%ecx;"
          "movl %%ecx, %[c_var];"
        : [c_var]"=r"(c_var_rol) 
    );
    printf("6) Vrednost c_var_rol: %d\n", c_var_rol);

    return 0;
} 