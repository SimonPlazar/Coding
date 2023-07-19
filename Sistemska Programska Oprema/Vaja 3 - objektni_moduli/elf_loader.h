#ifndef MY_ELF_LOADER_H
#define MY_ELF_LOADER_H

#include <elf.h>
#include <stdio.h>

void print_elf_header(Elf64_Ehdr *ehdr);
void read_elf_header(char* filename);

void print_elf_sections(Elf64_Shdr *shdr_table, int shnum, char *shstrtab);
void read_elf_sections(char* filename);

void print_elf_segment_info(Elf64_Ehdr *ehdr, Elf64_Phdr *phdr);
void read_elf_segment_info(char* filename);

void execute_elf(char* filename);

#endif // MY_ELF_LOADER_H