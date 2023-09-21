#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>


/**
 * Below is a program that 
 * that executes a command (with parameters)
 * received on their arguments in a new process,
 * waiting for the termination of that process.
 * 
 * 
 * Note the use of "foek" and "execvp" Linux API operations
 * 
 * This techique can be used to intercept a certain program execution
 */
 
int main(int argc, char *argv[]) {
	if (argc < 2) {
		fprintf(stderr, "usage: shell0 args...\n");
		exit(1);
	}
	
	int pchild = fork();
	
	if (pchild == -1) {
		perror("error on fork");
	}
	else if (pchild == 0) { // child
		if (execvp(argv[1], &argv[1]) == -1) {
			perror("error on exec cmd");
			exit(1);
		}
	}
	else {
		waitpid(pchild, NULL, 0);
	}
}
