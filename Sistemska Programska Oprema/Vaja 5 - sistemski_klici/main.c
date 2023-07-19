#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

#define SYS_WRITE 4
#define SYS_OPEN 5
#define SYS_CREAT 8
#define SYS_CHMOD 15
#define SYS_MKDIR 39
#define SYS_CHDIR 12
#define SYS_GETPID 20
#define SYS_TIME 13
#define SYS_CLOSE 6
#define SYS_SYNC 36

int main() {
    int rezultat;
    char *dir_name = "SysDir";

    // Ustvarjanje imenika (mape)
    asm("movl %1, %%eax;"
        "movl %2, %%ebx;"
        "movl %3, %%ecx;"
        "int $0x80;"
        "movl %%eax, %0;"
        : "=r"(rezultat)
        : "i"(SYS_MKDIR), "m"(dir_name), "i"(S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH)
        : "eax", "ebx", "ecx");

    if (rezultat < 0) {
        perror("Napaka pri ustvarjanju imenika");
        return 1;
    }

    // Prestavitev delovne poti v pravkar narejen imenik (mapo)
    asm("movl %1, %%eax;"
        "movl %2, %%ebx;"
        "int $0x80;"
        "movl %%eax, %0;"
        : "=r"(rezultat)
        : "i"(SYS_CHDIR), "m"(dir_name)
        : "eax", "ebx");

    if (rezultat < 0) {
        perror("Napaka pri spreminjanju delovne poti");
        return 1;
    }

    char *dat_name = "PidTimeData.dat";

    // Ustvarjanje zbirke (datoteke)
    int fd;
    asm("movl %1, %%eax;"
        "movl %2, %%ebx;"
        "movl %3, %%ecx;"
        "int $0x80;"
        "movl %%eax, %0;"
        : "=r"(fd)
        : "i"(SYS_CREAT), "m"(dat_name), "i"(S_IRUSR | S_IWUSR | S_IRGRP)
        : "eax", "ebx", "ecx");

        if (fd < 0) {
            perror("Napaka pri ustvarjanju zbirke");
            return 1;
        }

    // Pisanje v zbirko (datoteko)
    int pid;
    time_t cas;
    char buf[256];

    asm("movl %1, %%eax;"
        "int $0x80;"
        "movl %%eax, %0;"
        : "=r"(pid)
        : "i"(SYS_GETPID)
        : "eax");

    asm("movl %1, %%eax;"
        "movl %2, %%ecx;"
        "movl %%ecx, %%ebx;"
        "int $0x80;"
        "movl %%eax, %0;"
        : "=r"(cas)
        : "i"(SYS_TIME), "r"(&cas)
        : "eax", "ebx", "ecx");

    int dolzina = sprintf(buf, "PID: %d, Trenutni čas: %ld\n", pid, (long)cas);

    asm volatile (
        "movl $4, %%eax\n"    // syscall write
        "int $0x80\n"         // syscall
        : "=a"(rezultat)  // output
        : "b"(fd), "c"(buf), "d"(dolzina)  // input
        : "memory"  // clobbered
    );

    if (rezultat < 0) {
        perror("Napaka pri pisanju v datoteko");
        return 1;
    }

    // Zapiranje zbirke (datoteke)
    asm("movl %1, %%eax;"
        "movl %2, %%ebx;"
        "int $0x80;"
        "movl %%eax, %0;"
        : "=r"(rezultat)
        : "i"(SYS_CLOSE), "m"(fd)
        : "eax", "ebx");

    if (rezultat < 0) {
        perror("Napaka pri zapiranju zbirke");
        return 1;
    }

    // Klicanje "sync"
    asm("movl %1, %%eax;"
        "int $0x80;"
        "movl %%eax, %0;"
        : "=r"(rezultat)
        : "i"(SYS_SYNC)
        : "eax");

    if (rezultat < 0) {
        perror("Napaka pri sinhronizaciji datotečnega sistema");
        return 1;
    }

    return 0;
}

