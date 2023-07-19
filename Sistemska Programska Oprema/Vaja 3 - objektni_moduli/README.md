Razčlenitev in nalaganje formata ELF
Napišite preprosta programa v programskem jeziku C in GNU Assembler ter pripadajočo zbirko pravil za prevajanje Makefile, ki bosta prikazovala razčlenitev in nalaganje formata ELF.

 

Struktura projekta
Projekt naj vsebuje naslednje zbirke:

main.c - program v programskem jeziku C, ki razčleni, izpiše, naloži in zažene preprost program v zbirniku
poljubne dodatne zbirke .h in .c z deklaracijami in definicijami, ki jih uporabite v zbirki main.c
hello.asm - preprost program v zbirniku, ki ga boste razčlenili, izpisali, naložili in zagnali
Makefile - vsebuje pravila prevajanja
 

Zbirka Makefile:

vsebuje pravilo all
pravilo kliče pravili build in run
vsebuje pravilo build
pravilo kliče pravili build_elf_loader in build_hello
vsebuje pravilo build_elf_loader
pravilo iz zbirke main.c in vseh pomožnih zbirk zgradi program z imenom elf_loader
uporabite prevajalnik GCC
uporabite zastavice -Wall -Wextra -Wpedantic -Werror
vsebuje pravilo build_hello
pravilo iz zbirke hello.asm zgradi program z imenom hello
uporabite ukaz as -o hello.o hello.asm za zbiranje
uporabite ukaz ld -s -o hello hello.o za povezovanje
vsebuje pravilo run
pravilo zažene preveden program elf_loader z zastavico -r in obveznim argumentom hello
vsebuje pravilo clean
pravilo odstrani vse med prevajanjem ustvarjene zbirke
pravilo ne izpiše napake tudi v primeru, da katera izmed zbirk ne obstaja
 

Zbirka hello.asm:

Implementira preprost program v zbirniku GNU Assembler, ki na standardni izhod izpiše besedilo "Hello, world!". Uporabili ga boste kot testni program v formatu ELF za razčlenjevanje in nalaganje.

Ustvarite zbirko z imenom hello.asm in naslednjo vsebino:

.global _start

.text
_start:
    # write(1, msg, len)
    mov $1,   %rax
    mov $1,   %rdi
    mov $msg, %rsi
    mov $len, %rdx
    syscall

    # exit(0)
    mov $60,  %rax
    mov $0,   %rdi
    syscall

.data
msg:
    .ascii "Hello, world!n"
    .set    len, . - msg
 

Zbirka main.c:

Implementira delovanje programa elf_loader, ki omogoča razčlenitev in izpis formata ELF, ter njegovo nalaganje in izvajanje. Program naj podpira uporabo naslednjih zastavic, kot obvezni argument pa prejme pot do zbirke v formatu ELF, ki jo želimo analizirati:

elf_loader [-hSlr] elf_path

-h
  izpis zaglavja zbirke podane v elf_path

-S
  izpis tabele sekcij zbirke podane v elf_path

-l
  izpis tabele segmentov zbirke podane v elf_path

-r
  nalaganje in zagon programa podanega v elf_path
Programu lahko podamo več zastavic hkrati, izvedejo pa se v enakem vrstnem redu, kot so zapisane v zgornjem seznamu.

Ustvarite lahko poljubno število dodatnih zbirk .h in .c z deklaracijami in definicijami, ki jih uporabite v zbirki main.c, ter na tak način bolje strukturirate izvorno kodo programa.

 

Zastavica -h:

Naložite zbirko v formatu ELF, ki je podana preko poti elf_path, ter izpišite zaglavje formata ELF. Pri izpisu se skušajte približati izpisu, ki ga vrne ukaz readelf -W -h hello.

Primer uporabe:

$ ./elf_loader -h hello

ELF header
  Magic number:                      7F 45 4C 46 (0x7F ELF)
  Class:                             64-bit object
  Data:                              2's complement, little endian
  Version:                           1 (current)
  OS ABI:                            UNIX System V
  ABI version:                       0
  Type:                              Executable file
  Machine:                           AMD x86-64 architecture
  Version:                           1 (current)
  Entry point address:               0x401000
  Start of program headers:          64
  Start of section headers:          8232
  Flags:                             0x0
  Size of this header:               64 B
  Size of program headers:           56 B
  Number of program headers:         3
  Size of section headers:           64 B
  Number of section headers:         4
  Section header string table index: 3
 

Zastavica -S:

Naložite zbirko v formatu ELF, ki je podana preko poti elf_path, ter izpišite tabelo sekcij formata ELF. Pri izpisu se skušajte približati izpisu, ki ga vrne ukaz readelf -W -S hello.

Primer uporabe:

$ ./elf_loader -S hello

Section headers
  [Nr]  Name            Type           Flg    Address               Offset        Size          Link    Info    Align    EntSize
  [00]                  NULL                  0x0000000000000000    0x00000000    0x00000000    0       0       0        0
  [01]  .text           PROGBITS       AX     0x0000000000401000    0x00001000    0x0000002E    0       0       1        0
  [02]  .data           PROGBITS       WA     0x0000000000402000    0x00002000    0x0000000E    0       0       1        0
  [03]  .shstrtab       STRTAB                0x0000000000000000    0x0000200E    0x00000017    0       0       1        0
 

Zastavica -l:

Naložite zbirko v formatu ELF, ki je podana preko poti elf_path, ter izpišite tabelo segmentov formata ELF. Pri izpisu se skušajte približati izpisu, ki ga vrne ukaz readelf -W -l hello.

Primer uporabe:

$ ./elf_loader -l hello

Program headers
  Type    Flg    Offset        VirtAddr              PhysAddr              FileSize      MemSize       Align
  LOAD    R      0x00000000    0x0000000000400000    0x0000000000400000    0x000000E8    0x000000E8    0x00001000
  LOAD    R X    0x00001000    0x0000000000401000    0x0000000000401000    0x0000002E    0x0000002E    0x00001000
  LOAD    RW     0x00002000    0x0000000000402000    0x0000000000402000    0x0000000E    0x0000000E    0x00001000
 

Zastavica -r:

Naložite zbirko v formatu ELF, ki je podana preko poti elf_path, ter jo izvedite. To storite v več korakih v naslednjem vrstnem redu:

Iz tabele segmentov v pomnilnik preslikajte vse segmente tipa LOAD.
Za preslikavo uporabite sistemski klic mmap.
1. parameter je naslov preslikave v pomnilniku in mora biti enak vrednosti VirtAddr posameznega segmenta.
2. parameter je velikost preslikave, ki mora biti enaka vrednosti FileSize posameznega segmenta.
3. parameter je zaščita pomnilnika, ki jo nastavite glede na zastavice Flg posameznega segmenta.
4. parameter so zastavice preslikave, kjer uporabite MAP_PRIVATE.
5. parameter je oprimek datoteke ELF, ki ga dobite kot rezultat funkcije open nad podano potjo elf_path.
6. parameter je odmik preslikave od začetka zbirke, ki mora biti enaka vrednosti Offset posameznega segmenta.
Sistemski klic mmap uporabite za vsak segment tipa LOAD posebej.
Argumenti funkcije mmap naj ne bodo konstantne vrednosti, ampak prebrane iz tabele segmentov.
Ustvarite kazalec na funkcijo void func(void) in njegovo vrednost nastavite na vstopno točko programa (vrednost Entry point address iz zaglavja formata ELF).
void (*func)(void) = (void (*)(void)) 0x...;
Izvedite klic funkcije func.
func()
Odstranite vse preslikave s funkcijo munmap
Zaprete oprimek s funkcijo close
Primer uporabe:

$ ./elf_loader -r hello

Hello, world!
 

Pozor: Zgrajen nalagalnik formata ELF je zelo enostaven in posledično podpira nalaganje samo najbolj enostavnih in prirejenih programov. Nalagalnik namreč ne podpira prenaslavljanja, nalaganja deljenih/dinamičnih knjižnic, uporabe argumentov programa, vračanja vrednosti, itd...

 

Oddaja rešitve
Pri implementaciji rešitve bodite posebej pozorni na naslednje stvari:

program elf_loader je napisan v programskem jeziku C
program hello je napisan v zbirniku GNU Assembler
program elf_loader se prevede s prevajalnikom GCC in zastavicami -Wall -Wextra -Wpedantic -Werror
program hello se prevede z ukazoma as in ld
argumenti v funkcijo mmap niso konstantne vrednosti, ampak prebrane iz tabele segmentov
pravilo clean ne izpiše napake tudi v primeru, da katera izmed zbirk ne obstaja
Na sistem za vaje oddajte arhiv zip, ki vsebuje celoten projekt (Makefile, main.c, hello.asm, poljubne .h in .c zbirke) z vašo implementacijo.