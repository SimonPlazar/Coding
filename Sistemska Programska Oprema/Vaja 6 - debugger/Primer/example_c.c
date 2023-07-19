#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ptrace.h>
#include <sys/user.h>
#include <sys/wait.h>
#include <unistd.h>

#include "misc.h"

static void
run_parent(pid_t pid)
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

	// Kopiraj vrednosti registrov procesa z ID-jem pid (otroka) v strukturo
	// user_regs_struct
	struct user_regs_struct uregs;
	r = ptrace(PTRACE_GETREGS, pid, NULL, &uregs);
	check_ptrace(r);

	// Izpisi vrednost registra ebx
	printf("Parent> Register ebx: %ld\n", uregs.ebx);

	// Izpisi vrednosti registra eip - instruction pointer
	long ins = ptrace(PTRACE_PEEKTEXT, pid, uregs.eip, 0);
	printf("Parent> Val: %lx Ins: %lx\n", uregs.eip, ins);

	// Nastavi novo vrednost registra ebx v strukturi user_regs_struct
	uregs.ebx = 245;

	// Spremeni vrednosti registrov procesa z ID-jem pid (otroka) z vrednostmi
	// iz strukture user_regs_struct
	r = ptrace(PTRACE_SETREGS, pid, NULL, &uregs);
	check_ptrace(r);

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
	char *c_pathname = "./example_c_child";
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
		run_child();
		break;
	default:
		// Stars (parent process)
		run_parent(pid);
		break;
	}

	return 0;
}
