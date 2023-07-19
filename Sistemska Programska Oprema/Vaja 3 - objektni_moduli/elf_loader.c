#include "elf_loader.h"
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <elf.h>

void print_elf_header(Elf64_Ehdr *ehdr)
{
    printf("ELF Header:\n");
    printf("  Magic:   ");
    for (int i = 0; i < EI_NIDENT; i++) {
        printf("%02x ", ehdr->e_ident[i]);
    }
    printf("\n");
    printf("  Class:                             %s\n", (ehdr->e_ident[EI_CLASS] == ELFCLASS64) ? "ELF64" : "Unknown");
    printf("  Data:                              %s\n", (ehdr->e_ident[EI_DATA] == ELFDATA2LSB) ? "2's complement, little endian" : "Unknown");
    printf("  Version:                           %d\n", ehdr->e_ident[EI_VERSION]);
    printf("  OS/ABI:                            %s\n", (ehdr->e_ident[EI_OSABI] == ELFOSABI_SYSV) ? "UNIX - System V" : "Unknown");
    printf("  ABI Version:                       %d\n", ehdr->e_ident[EI_ABIVERSION]);
    printf("  Type:                              0x%x\n", ehdr->e_type);
    printf("  Machine:                           %s\n", (ehdr->e_machine == EM_X86_64) ? "Advanced Micro Devices X86-64" : "Unknown");
    printf("  Version:                           0x%x\n", ehdr->e_version);
    printf("  Entry point address:               0x%lx\n", ehdr->e_entry);
    printf("  Start of program headers:          %ld (bytes into file)\n", ehdr->e_phoff);
    printf("  Start of section headers:          %ld (bytes into file)\n", ehdr->e_shoff);
    printf("  Flags:                             0x%x\n", ehdr->e_flags);
    printf("  Size of this header:               %d (bytes)\n", ehdr->e_ehsize);
    printf("  Size of program headers:           %d (bytes)\n", ehdr->e_phentsize);
    printf("  Number of program headers:         %d\n", ehdr->e_phnum);
    printf("  Size of section headers:           %d (bytes)\n", ehdr->e_shentsize);
    printf("  Number of section headers:         %d\n", ehdr->e_shnum);
    printf("  Section header string table index: %d\n", ehdr->e_shstrndx);
}

void read_elf_header(char* filename) {
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
    printf("Unable to open '%s'\n", filename);
    return;
    }

    Elf64_Ehdr ehdr;
    if (fread(&ehdr, sizeof(ehdr), 1, fp) != 1) {
    printf("Error fread\n");
    fclose(fp);
    return;
    }

    print_elf_header(&ehdr);

    fclose(fp);
    return;
}

char *get_section_type_name(unsigned int type) {
    switch(type) {
        case SHT_NULL: return "NULL";
        case SHT_PROGBITS: return "PROGBITS";
        case SHT_SYMTAB: return "SYMTAB";
        case SHT_STRTAB: return "STRTAB";
        case SHT_RELA: return "RELA";
        case SHT_HASH: return "HASH";
        case SHT_DYNAMIC: return "DYNAMIC";
        case SHT_NOTE: return "NOTE";
        case SHT_NOBITS: return "NOBITS";
        case SHT_REL: return "REL";
        case SHT_SHLIB: return "SHLIB";
        case SHT_DYNSYM: return "DYNSYM";
        case SHT_INIT_ARRAY: return "INIT_ARRAY";
        case SHT_FINI_ARRAY: return "FINI_ARRAY";
        case SHT_PREINIT_ARRAY: return "PREINIT_ARRAY";
        case SHT_GROUP: return "GROUP";
        case SHT_SYMTAB_SHNDX: return "SYMTAB SECTION INDICES";
        default: return "UNKNOWN";
    }
}

void print_elf_sections(Elf64_Shdr *shdr_table, int shnum, char *shstrtab) {
    printf("There are %d section headers, starting at offset 0x%lx:\n\n", shnum, shdr_table[0].sh_offset);

    printf("Section Headers:\n");
    printf("  [Nr] Name              Type            Address          Offset       Size              EntSize         Flags  Link  Info  Align\n");

    for (int i = 0; i < shnum; i++) {
        char *section_name = shstrtab + shdr_table[i].sh_name;
        char *section_type = get_section_type_name(shdr_table[i].sh_type);
        printf("  [%2d] %-17s %-15s %016lx  %06lx        %016lx  %016lx  %-6lu %-5u %-5u %lu\n", 
                i, section_name, section_type, shdr_table[i].sh_addr, shdr_table[i].sh_offset, 
                shdr_table[i].sh_size, shdr_table[i].sh_entsize, shdr_table[i].sh_flags,
                shdr_table[i].sh_link, shdr_table[i].sh_info, shdr_table[i].sh_addralign
                );
    }
}

void read_elf_sections(char* filename) {
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        printf("Unable to open '%s'\n", filename);
        return;
    }

    Elf64_Ehdr ehdr;
    if (fread(&ehdr, sizeof(ehdr), 1, fp) != 1) {
        printf("Error fread\n");
        fclose(fp);
        return;
    }

    Elf64_Shdr shdr_table[ehdr.e_shnum];
    if (fseek(fp, ehdr.e_shoff, SEEK_SET) != 0) {
        printf("Error fseek\n");
        fclose(fp);
        return;
    }
    if (fread(shdr_table, sizeof(Elf64_Shdr), ehdr.e_shnum, fp) != ehdr.e_shnum) {
        printf("Error fread\n");
        fclose(fp);
        return;
    }

    char *shstrtab = NULL;
    if (ehdr.e_shstrndx != SHN_UNDEF) {
        if (fseek(fp, shdr_table[ehdr.e_shstrndx].sh_offset, SEEK_SET) != 0) {
            printf("Error fseek\n");
            fclose(fp);
            return;
        }
        shstrtab = malloc(shdr_table[ehdr.e_shstrndx].sh_size);
        if (shstrtab == NULL) {
            printf("Error malloc\n");
            fclose(fp);
            return;
        }
        if (fread(shstrtab, sizeof(char), shdr_table[ehdr.e_shstrndx].sh_size, fp) != shdr_table[ehdr.e_shstrndx].sh_size) {
            printf("Error fread\n");
            fclose(fp);
            free(shstrtab);
            return;
        }
    }

    print_elf_sections(shdr_table, ehdr.e_shnum, shstrtab);

    if (shstrtab != NULL) {
        free(shstrtab);
    }
    fclose(fp);
    return;
}

void print_elf_segment_info(Elf64_Ehdr *ehdr, Elf64_Phdr *phdr) {

    printf("Elf file type is %s\n", (ehdr->e_type == ET_EXEC) ? "EXEC (Executable file)" : "Unknown");
    printf("Entry point 0x%lx\n", ehdr->e_entry);
    printf("There are %d program headers, starting at offset %ld\n", ehdr->e_phnum, ehdr->e_phoff);
    printf("Program Headers:\n");
    printf("  Type           Offset             VirtAddr           PhysAddr           FileSiz            MemSiz             Flg Align\n");
        
    for (int i = 0; i < ehdr->e_phnum; i++) {
        printf("  %-15s 0x%016lx 0x%016lx 0x%016lx 0x%016lx 0x%016lx %-3s 0x%lx\n",
               (phdr->p_type == PT_LOAD) ? "LOAD" : "Unknown",
               phdr->p_offset,
               phdr->p_vaddr,
               phdr->p_paddr,
               phdr->p_filesz,
               phdr->p_memsz,
               (phdr->p_flags & PF_R) ? ((phdr->p_flags & PF_W) ? ((phdr->p_flags & PF_X) ? "R E" : "R  ") : ((phdr->p_flags & PF_X) ? "R  " : "R  ")) : ((phdr->p_flags & PF_W) ? ((phdr->p_flags & PF_X) ? "  E" : "W  ") : ((phdr->p_flags & PF_X) ? "   " : "    ")),
               phdr->p_align);
    }
}

void read_elf_segment_info(char* filename)
{
    FILE* fp = fopen(filename, "rb");
    if (fp == NULL) {
        printf("Unable to open '%s'\n", filename);
        return;
    }

    Elf64_Ehdr ehdr;
    if (fread(&ehdr, sizeof(ehdr), 1, fp) != 1) {
        printf("Error fread\n");
        fclose(fp);
        return;
    }

    if (memcmp(ehdr.e_ident, ELFMAG, SELFMAG) != 0) {
        printf("Invalid ELF header\n");
        fclose(fp);
        return;
    }

    Elf64_Phdr phdr;
    if (fread(&phdr, sizeof(phdr), 1, fp) != 1) {
        printf("Error fread\n");
        fclose(fp);
        return;
    }

    print_elf_segment_info(&ehdr, &phdr);

    fclose(fp);
}

void execute_elf(char *filename) 
{
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    Elf64_Ehdr elf_header;
    if (read(fd, &elf_header, sizeof(elf_header)) != sizeof(elf_header)) {
        perror("read");
        exit(1);
    }

    if (memcmp(elf_header.e_ident, ELFMAG, SELFMAG) != 0) {
        fprintf(stderr, "Datoteka \"%s\" ni v formatu ELF.\n", filename);
        exit(1);
    }

    Elf64_Phdr *program_headers = malloc(elf_header.e_phnum * sizeof(Elf64_Phdr));
    if (program_headers == NULL) {
        perror("malloc");
        exit(1);
    }
    if (lseek(fd, elf_header.e_phoff, SEEK_SET) == -1) {
        perror("lseek");
        exit(1);
    }
    if (read(fd, program_headers, elf_header.e_phnum * sizeof(Elf64_Phdr)) != (ssize_t)(elf_header.e_phnum * sizeof(Elf64_Phdr))) {
        perror("read");
        exit(1);
    }

    for (int i = 0; i < elf_header.e_phnum; i++) {
        if (program_headers[i].p_type == PT_LOAD) {
            void *addr = (void *)program_headers[i].p_vaddr;
            size_t size = program_headers[i].p_filesz;
            int prot = 0;
            if (program_headers[i].p_flags & PF_R) prot |= PROT_READ;
            if (program_headers[i].p_flags & PF_W) prot |= PROT_WRITE;
            if (program_headers[i].p_flags & PF_X) prot |= PROT_EXEC;
            void *map = mmap(addr, size, prot, MAP_PRIVATE, fd, program_headers[i].p_offset);
            if (map == MAP_FAILED) {
                perror("mmap");
                exit(1);
            }
        }
    }

    void (*func)(void) = (void (*)(void))(elf_header.e_entry);

    func();

    for (int i = 0; i < elf_header.e_phnum; i++) {
        if (program_headers[i].p_type == PT_LOAD) {
            void *addr = (void *)program_headers[i].p_vaddr;
            size_t size = program_headers[i].p_filesz;
            if (munmap(addr, size) == -1) {
                perror("munmap");
                exit(1);
            }
        }
    }

    if (close(fd) == -1) {
        perror("close");
        exit(1);
    }
}