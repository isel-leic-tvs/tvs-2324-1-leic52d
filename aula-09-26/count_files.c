/**
 * this program ilustrates the creation of compound commands
 * by creating pipelines between existing processes
 * In this case a pipeline between ls and wc is manually created
 * using linux mechanisms directly
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
	int p[2];
	
	// criação do pipe
	pipe(p);
	
	// ls creation
	int pchild_ls = fork();
	
	if (pchild_ls == 0) { //child
		close(p[0]); 
		dup2(p[1], STDOUT_FILENO); // duplicate pipe output as standard output
		
		close(p[1]); // already duplicated on standard output
		execlp("ls", "ls", NULL);
		exit(1);
	}
	// parent
	
	// wc creation
	int pchild_wc = fork();
	if (pchild_wc == 0) { //child
		close(p[1]);
		dup2(p[0], STDIN_FILENO); // duplicate pipe input as standard input
		
		close(p[0]);  // already duplicated on standard input
		execlp("wc", "wc", "-w", NULL);
		exit(1);
	} 
	
	// close pipe descriptors
	close(p[0]);
	close(p[1]);
	
	
	// wait for both childs
	waitpid(pchild_ls, NULL, 0);
	waitpid(pchild_wc, NULL, 0);
	
	return 0;
}
	
	

