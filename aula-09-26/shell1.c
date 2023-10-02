#include <stdio.h>

#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <stdbool.h>
#include <signal.h>


/**
 * The program below is a minimal shell
 * is able to read simple commands (without parameters)
 * and execute them on a new process, waiting for his termination.
 *
 */

#define EXIT_CMD "exit"
#define BACKGROUND_EXEC '&'


void sigint_handler(int n) {
	printf("SIGINT(%d)!\n", n);
}

void sigchld_handler(int n) {
	printf("SIGCHLD(%d)!\n", n);
	while (waitpid(-1, NULL, WNOHANG) >0);
}
 
int main(int argc, char *argv[]) {
	char line[256];
	bool in_background;
	
	// ignorar o signal SIGINT
	signal(SIGINT, sigint_handler);
	
	// processing terminated childs
	signal(SIGCHLD, sigchld_handler);
	while(1) {
		printf("> ");
		fgets(line, 256, stdin);
		line[strlen(line)-1] = 0; // discard line termination char
		if (line[0] == 0) continue; // empty line
		
		// check background execution
		if (line[strlen(line)-1] == BACKGROUND_EXEC) {
			in_background = true;
			line[strlen(line)-1] = 0;
		}
		else {
			in_background = false;
		}
		
		// check internal command (exit)
		if (strcmp(line, EXIT_CMD) ==0) 
			break;
		
		int pchild = fork();
	
		
		if (pchild == -1) {
			perror("error on fork");
		}
		else if (pchild == 0) { // child
			if (execlp(line, line, NULL) == -1) {
				perror("error on exec cmd");
				exit(1);
			}
		}
		else {
			if (!in_background) 
				waitpid(pchild, NULL, 0);
		}
	}
	
	return 0;
}
