#include <stdio.h>

#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>


/**
 * The program below is a minimal shell
 * is able to read simple commands (without parameters)
 * and execute them on a new process, waiting for his termination.
 *
 */
 
int main(int argc, char *argv[]) {
	char line[256];
	
	while(1) {
		printf("> ");
		fgets(line, 256, stdin);
		line[strlen(line)-1] = 0; // discard line termination char
		
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
			waitpid(pchild, NULL, 0);
		}
	}
	
	
}
