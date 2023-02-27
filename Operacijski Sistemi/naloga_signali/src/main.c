#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

#include "common.h"

volatile int procesi_diff = 0;
volatile bool sigint = false;
volatile bool sigterm = false;

void sig_handler(int sig){
	if (sig == SIGALRM) alarm(procesi_diff);
	if (sig == SIGINT) sigint = true;
	if (sig == SIGTERM) sigterm = true;
}

int main(int argc, char **argv){
	if (argc != 2){
		fprintf(stderr, "Manjka config file\n");
		return 1;
	}
	
	int razlika_casov = 0;
	
	if (signal(SIGALRM, sig_handler) < 0){
		perror ("sigaction");
		return 1;
	}
	if (signal(SIGINT, sig_handler) < 0){
		perror ("sigaction");
		return 1;
	}
	if (signal(SIGTERM, sig_handler) < 0){
		perror ("sigaction");
		return 1;
	}
	
	struct job_node *job_list = read_job_list(argv[1]);
	struct job_node *job_node = job_list;
	
	while (job_node != NULL){
		razlika_casov = difftime(job_node->time, time(NULL));
		if (razlika_casov > 0){ // v prihodnosti ali trenutno
			if (job_node->next != NULL){
				procesi_diff = difftime(job_node->next->time, job_node->time);
				alarm(razlika_casov);
				pause();
				if (sigint == true || sigterm == true) break;
				else system(job_node->cmd);
			}else{
				alarm(razlika_casov);
				pause();
				if (sigint == true || sigterm == true) break;
				else system(job_node->cmd);
			}
		}else{ // v preteklosti
			if (sigint == true || sigterm == true) break;
			else system(job_node->cmd);
		}
		job_node = job_node->next;
	}
	
	while (job_node != NULL){
		printf("%ld %s\n", job_node->time, job_node->cmd);
		job_node = job_node->next;
	}
	
	free_job_list(job_list); 
	
	return 0;
}
