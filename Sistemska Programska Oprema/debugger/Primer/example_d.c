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

	// Pocakaj, da proces z ID-jem pid (otrok) zamenja status (se ustavi).
	waitpid(pid, NULL, 0);

	// Zazeni ustavljen proces z ID-jem pid (otroka)
	long r = ptrace(PTRACE_CONT, pid, 0, 0);
	check_ptrace(r);

	// Pocakamo nekaj sekund, da se otrok izvaja
	sleep(5);

	// Procesu z ID-jem pid (otroku) poslji signal SIGINT
	// Izvajanje procesa se bo ustavilo
	kill(pid, SIGINT);

	// Pocakaj, da proces z ID-jem pid (otrok) zamenja status (se ustavi).
	waitpid(pid, NULL, 0);

	// Zacetni naslov nalozenega programa v pomnilniku se lahko spreminja, zato
	// je potrebno zacetni naslov prebrati ko je program ze nalozen v pomnilnik.
	// Tabela preslikav pomnilniskih lokacij za posamezen proces se nahaja v
	// "/proc/<pid>/maps".
	// https://en.wikipedia.org/wiki/Position-independent_code
	// https://en.wikipedia.org/wiki/Address_space_layout_randomization

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

	// Naslov spremenljivke v
	// $ nm example_d_child
	unsigned long addr = 0x00004008;

	// Izpis zacetnega naslova in naslova spremenljivke v
	printf("Parent> Child start address: 0x%lx\n", start_addr);
	printf("Parent> Detected child address of variable v_var: 0x%lx\n", start_addr + addr);

	// Preberi vrednost na naslovu start_addr + addr
	long data = 0;
	data = ptrace(PTRACE_PEEKDATA, pid, start_addr + addr, NULL);
	check_ptrace(data);

	// Izpisi prebrano vrednost
	printf("Parent> Value of v_var: %ld\n", data);

	// Spremeni vrednost
	data = 240;

	// Kopiraj spremenjeno vrednost na naslov start_addr + addr
	r = ptrace(PTRACE_POKEDATA, pid, start_addr + addr, data);
	check_ptrace(data);

	// Zazeni ustavljen proces z ID-jem pid (otroka)
	r = ptrace(PTRACE_CONT, pid, NULL, NULL);
	check_ptrace(r);

	// Pocakaj, da proces z ID-jem pid (otrok) zamenja status
	// (proces (otrok) je koncal z izvajanjem ali pa je prejel kak drug signal)
	int wstatus;
	waitpid(pid, &wstatus, 0);
	check_waitpid_status(wstatus);

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
	char *c_pathname = "./example_d_child";
	char *c_argv[] = { c_pathname, NULL };
	char *c_envp[] = { NULL };

	int rr = execve(c_pathname, c_argv, c_envp);
	check_execve(rr);
}

int main()
{
	// Ustvari nov proces
	pid_t pid = fork();

	switch (pid) {
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
