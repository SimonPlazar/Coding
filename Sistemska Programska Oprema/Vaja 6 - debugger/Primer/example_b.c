#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/user.h>

#include "misc.h"

static void run_parent(pid_t pid)
{
	printf("Parent> Begin\n");

	// Pocakaj, da proces z ID-jem pid (otrok) zamenja status.
	// Ker smo funkcijo execve() v procesu (otroku) klicali za funkcijo
	// ptrace(PTRACE_TRACEME, ...), se izvajanje procesa (otroka) ustavi takoj
	// ob zagonu  - procesu (otroku) je bil poslan signal SIGTRAP.

	int wstatus;
	waitpid(pid, &wstatus, 0);
	check_waitpid_status(wstatus);

	// Pocakamo nekaj sekund, preden zazenemo ustavljen proces (otroka)
	for (int32_t i = 10; i > 0; i--)
	{
		printf("Parent> Child start in %d s\n", i);
		fflush(stdout);
		sleep(1);
	}

	// Zazeni ustavljen proces z ID-jem pid (otroka)
	long rr = ptrace(PTRACE_CONT, pid, 0, 0);
	check_ptrace(rr);

	// Pocakaj, da proces z ID-jem pid (otrok) zamenja status
	// (proces (otrok) je koncal z izvajanjem ali pa je prejel kak drug signal)
	waitpid(pid, NULL, 0);

	printf("Parent> End\n");
}

static void
run_child()
{
	// Omogoci, da bo trenutnemu procesu lahko sledil stars
	long r = ptrace(PTRACE_TRACEME, 0, NULL, NULL);
	check_ptrace(r);

	// Program, ki se izvaja v trenutnem procesu, zamenjaj s programom c_pathname.
	// Sklad, kopica ter segmenta inicializiranih in neinicializiranih podatkov
	// se ponovno inicializirajo.
	char *c_pathname = "./example_b_child";
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
			run_child();
			break;
		default:
			// Stars (parent process)
			run_parent(pid);
			break;
	}

	return 0;
}
