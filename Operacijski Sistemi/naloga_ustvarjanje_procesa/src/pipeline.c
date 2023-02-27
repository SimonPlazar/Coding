#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>

int execute_pipeline(char*** cmd_list, int input_fd, int final_output_fd, int err_fd) {
	int next_input_fd = -1;
	int output_fd = -1;
	char return_val = 0;
	
	for(char***cmd=cmd_list; cmd[0]!=0; cmd+=1){
		char** args = cmd[0]; //tabela ukaza procesa
		int status = 0;
		
		//če je zadnji proces preusmeri na glavni izhod
		if ((cmd+1)[0] == 0) output_fd = final_output_fd;
		
		//drugače naredi pipo iz tega procesa v nesladnjega
		else{
			int pipe_fd[2];
			if (pipe(pipe_fd) != 0) {
				fprintf(stderr, "error pipe");
				return -1;
			}
			next_input_fd = pipe_fd[0];
			output_fd = pipe_fd[1];
		}
		
		int new_pid = 0;
		switch(fork()){
			case -1:
				fprintf(stderr, "error fork");
				return -1;
				break;
			
			case 0:
				new_pid = getpid(); //dobi pid otroka
				
				//vse kar bo program bral z fd 0 bere z input_fd
				if (dup2(input_fd, 0) == -1) {
					fprintf(stderr, "error dup in");
					return -1;
				}
				//vse kar bo program pisal na fd 1 gre na output_fd
				if (dup2(output_fd, 1) == -1) {
					fprintf(stderr, "error dup out");
					return -1;
				}
				//vse kar bo program pisal na fd 2 gre na err_fd
				if (dup2(err_fd, 2) == -1) {
					fprintf(stderr, "error dup err");
					return -1;
				}
				
				//zapremo opriimke
				if (input_fd != 0) close(input_fd);
				if (output_fd != 1) close(output_fd);
				if (err_fd != 2) close(err_fd);
				
				if(execvp(args[0], args)==-1){
					fprintf(stderr, "error exec");
					return -1;
				}
				break;
				
			default:
				close(input_fd);
				if ((cmd+1)[0] != 0) close(output_fd);
				input_fd = next_input_fd;
				
				//pomoc pri kodi
				//https://stackoverflow.com/questions/27306764/capturing-exit-status-code-of-child-process
				//pocakamo da se proces konca ali ga zbrisemo (zombi)
				if (waitpid(new_pid, &status, 0) == -1) {
					fprintf(stderr, "error waitpid");
					return_val = -1;
				}
				
				if (return_val == 0) {
					//ce se je child proces normalno koncal potem true
					if (WIFEXITED(status)) {
						//const int es = WEXITSTATUS(status);
						return_val = WEXITSTATUS(status);
						//printf("exit status was %d\n", es);
					}else return_val = 255;
				}
				break;
		}
	}
	return return_val;
}
