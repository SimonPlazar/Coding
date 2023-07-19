# Uvod

## Linux distribucije:
- Ubuntu
- Mint
- Fedora

## Namestitev:
- primarni in edini sistem
- poleg sistema Windows/MacOS (dual boot)
- virtualizacija (VirtualBox)
- Windows Subsystem for Linux - WSL ???

# Ponovitev programskega jezika C

## Struktura projekta

Makefile - vsebuje pravila za prevajanje

main.c - vsebuje main funkcijo

my_func.h - vsebuje deklaracijo preproste funkcije

my_func.c - vsebuje definicijo preproste funckije

my_struct.h - vsebuje deklaracijo preproste strukture

## Prevajanje projekta

Z direktnim klicem prevajalnika gcc:  
```$ gcc -o my_exec main.c (NAPAKA: undefined reference to 'my_func')```

Z direktnim klicem prevajalnika gcc:  
```$ gcc -o my_exec main.c my_func.c```

S pomočjo orodja make:  
```$ make build``` - izvede pravilo *build* in prevede program

```$ make run``` - izvede pravilo *run* in zažene program

```$ make all``` - izvede pravilo *all*, ki izvede pravili *build* ter *run* in prevede ter zažene program

```$ make``` - izvede privzeto pravilo *all* (prvo pravilo znotraj zbirke Makefile)

```$ make clean``` - izvede pravilo *clean* in pobriše ustvarjene zbirke

## Makefile

Datoteka Makefile je sestavljena iz enega ali več pravil, pri čemer ima
posamezno pravilo naslednjo obliko:

```
cilj: odvisnosti
    ukazi
```
