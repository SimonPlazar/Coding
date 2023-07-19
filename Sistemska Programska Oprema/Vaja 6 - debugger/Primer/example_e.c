#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ptrace.h>
#include <sys/user.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/personality.h>

#include "misc.h"

static void run_parent(pid_t pid)
{
	printf("Parent> Begin\n");

	// Pocakaj, da proces z ID-jem pid (otrok) zamenja status.
	// Ker smo funkcijo execve() v procesu (otroku) klicali za funkcijo
	// ptrace(PTRACE_TRACEME, ...), se izvajanje procesa (otroka) ustavi takoj
	// ob zagonu - procesu (otroku) je bil poslan signal SIGTRAP.

	int wstatus;
	waitpid(pid, &wstatus, 0);
	check_waitpid_status(wstatus);

	// Odpri datoteko /proc/<pid>/maps
	char path[100] = { 0 };
	sprintf(path, "/proc/%d/maps", pid);
	int fd = open(path, O_RDONLY);

	// Preberi zacetek datoteke
	char temp[100] = { 0 };
	read(fd, temp, 100);
	close(fd);

	// Vrednost, ki nas zanima (zacetni naslov nalozenega programa), se nahaja
	// takoj od zacetka datoteke do prve pojave znaka '-'.
	char *del = strchr(temp, '-');
	*del = 0;

	// Pretvori niz v sestnajstisko stevilo
	// Zacetni naslov
	unsigned long start_addr = strtol(temp, NULL, 16);

	// Naslov prekinitve
	// objdump -d example_e_child
	unsigned long addr = 0x1214;

	// Izpis zacetnega naslova in naslova
	printf("Parent> Child start address: 0x%lx\n", start_addr);
	printf("Parent> Breakpoint address: 0x%lx\n", start_addr + addr);

	// Preberi vrednost na naslovu start_addr + addr
	// Shranimo kar je trenutno na lokaciji
	long data = ptrace(PTRACE_PEEKDATA, pid, start_addr + addr, NULL);
	printf("Parent> Ins: 0x%lx\n", data);

	// Nastavimo prekinitev
	// Prekinitev izvedemo tako, da na izbran naslov zapisemo posebno instrukcijo - int 3 oz. 0xcc

	// Nova instrukcija - Zakaj samo zadnja dva byta?
	// Preverimo z objdump
	long int_data = (data & ~0xff) | 0xcc;
	printf("Parent> New Ins: 0x%lx\n", int_data);

	// Kopiraj spremenjeno vrednost na naslov start_addr + addr
	long r = ptrace(PTRACE_POKEDATA, pid, start_addr + addr, int_data);
	check_ptrace(r);

	// Zazeni ustavljen proces z ID-jem pid (otroka)
	r = ptrace(PTRACE_CONT, pid, NULL, NULL);
	check_ptrace(r);
	waitpid(pid, NULL, 0);

	// Dosegli smo prekinitev
	printf("Nadaljuj...");
	getchar();

	// Vrnimo izvoren ukaz
	r = ptrace(PTRACE_POKEDATA, pid, start_addr + addr, data);
	check_ptrace(r);

	// Popravimo eip register - Zakaj?
	struct user_regs_struct uregs;
	ptrace(PTRACE_GETREGS, pid, NULL, &uregs);
	uregs.eip = start_addr + addr;
	ptrace(PTRACE_SETREGS, pid, NULL, &uregs);

	// Zazeni ustavljen proces z ID-jem pid (otroka)
	r = ptrace(PTRACE_CONT, pid, NULL, NULL);
	check_ptrace(r);
	waitpid(pid, NULL, 0);

	printf("Parent> End\n");
}

static void run_child()
{
	// Omogoci, da bo trenutnemu procesu lahko sledil stars
	long r = ptrace(PTRACE_TRACEME, 0, NULL, NULL);
	check_ptrace(r);

	// Program, ki se izvaja v trenutnem procesu, zamenjaj s programom c_pathname.
	// Sklad, kopica ter segmenta inicializiranih in neinicializiranih podatkov
	// se ponovno inicializirajo.
	char *c_pathname = "./example_e_child";
	char *c_argv[] = { c_pathname, NULL };
	char *c_envp[] = { NULL };

	int rr = execve(c_pathname, c_argv, c_envp);
	check_execve(rr);

	// Ker smo funkcijo execve() v procesu (otroku) klicali za funkcijo
	// ptrace(PTRACE_TRACEME, ...), se izvajanje procesa (otroka) ustavi takoj
	// ob zagonu - procesu (otroku) je bil poslan signal SIGTRAP.
}

int main()
{
	// Ustvari nov proces
	pid_t pid = fork();

	switch (pid)
	{
		case -1:
			// Napaka
			perror("fork");
			exit(-1);
			break;
		case 0:
			// Otrok (child process)
			personality(ADDR_NO_RANDOMIZE);
			run_child();
			break;
		default:
			// Stars (parent process)
			run_parent(pid);
			break;
	}

	return 0;
}
