# Objektni moduli

## ELF format

ELF format se uporablja za:

- objektne zbirke (object files)
- binarne zbirke (binaries)
- deljene/dinamične knjižnice (shared libraries)
- zbirke z izvlečki (core dumps)

ELF format je sestavljen iz naslednjih zaglavij:

- zaglavje formata ELF (ELF header)
- tabela z zaglavji programa (program *header table)
  - pogled izvajanja (execution view)
  - opisuje nobenega ali več pomnilniških segmentov (describing zero or more memory segments)
- tabela z zaglavji sekcij (section header table)
  - pogled povezovanja (linking view)
  - opisuje nobenega ali več sekcij (describing zero or more sections)

Dokumentacija formata ELF:

``` bash
man elf
```

## Ukazi za prevajanje testnega programa

Zbiranje zbirne kode v objektno kodo in nato njeno povezovanje v izvedljivo strojno kodo:

``` bash
as -o hello.o hello.asm
ld -o hello hello.o
```

Prevajanje zbirke z izvorno kodo v izvedljivo strojno kodo:

```
gcc -o hello hello.c
```

Odstranjevanje simbolov iz objektnih zbirk:

```
strip -s hello
```

Preveri razliko v zbirkah ELF z neodstranjenimi in odstranjenimi simboli.
Preveri razliko v zbirkah ELF zgrajenih iz zbirk hello.asm in hello.c.

## Ukazi za analizo formata ELF

Zagon prevedenega programa:

```
./hello
```

Izpis vsebine prevedenega programa v šestnajstiški obliki:

```
hexdump -C hello
```

Izpis zaglavja formata ELF:

```
readelf -W -h hello
```

Izpis tabele sekcij formata ELF:

```
readelf -W -S hello
```

Izpis tabele segmentov formata ELF:

```
readelf -W -l hello
```

Izpis tabele simbolov:

```
readelf -W -s hello
```

Izpis podatkovne sekcije v šestnajstiški obliki:

```
readelf -x .data hello
```

Alternativna oblika:

```
objdump -s -j .data hello
```

Izpis programske sekcije v šestnajstiški obliki:

```
readelf -x .text hello
```

Alternativna oblika z vklopljenim disassembler-jem:

``` bash
objdump -d -j .text hello
```

Izpis tabele z imeni sekcij:

``` bash
readelf -x .shstrtab hello
```

Knjiznica za branje in pisanje ELF formatov:

``` c
#include <elf.h>

switch(data):
  case ELFCLASS32:
    // 32-bit ELF
  case ELFCLASS64:
    // 64-bit ELF
  default:
    // unknown ELF class

//cast pointer na object iz te knjiznice in klici atribute
```

## Viri

Dokumentacija formata ELF:

<http://www.skyfree.org/linux/references/ELF_Format.pdf>

<https://en.wikipedia.org/wiki/Executable_and_Linkable_Format>

Analiza formata ELF:

<https://suchprogramming.com/exploring-elf/>

<https://blog.k3170makan.com/p/series.html>

Dokumentacija zbirnika GNU:

<https://sourceware.org/binutils/docs/as/index.html>

Tabela sistemskih klicev:

<https://filippo.io/linux-syscall-table/>
