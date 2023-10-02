#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

/**
 * this program uses a pipe to create a communication
 * channel between the child (the producer) and the parent (the consumer)
 */
 
#define MAX_MSG_SIZE 256

int main() {
	
	int p[2];
	if (pipe(p) == -1) {
		perror("error creating pipe");
		exit(1);
	}
	
	int pchild = fork();
	if (pchild == -1) {
		perror("error creating child process");
		exit(2);
	}
	else if (pchild == 0) { // child process code
		char msg[MAX_MSG_SIZE];
		sprintf(msg, "hello from child %d\n", getpid());
		
		close(p[0]); // o descritor que permite leitura não é necessário no filho
		write(p[1], msg, strlen(msg)+1);
		exit(0);
	}
	else { // parent code
		
		// the pipe fd that supports writes MUST be closed here
		// if not, with parent as a potencial writer on pipe,
		// the read loop on pipe below will deadlock!
		close(p[1]);  
		
		char child_msg[MAX_MSG_SIZE];
		int curr_pos = 0; // current buffer position
		int nr;           // total of read bytes
		
		
		
		waitpid(pchild, NULL, 0); // wait for child termination
		
		
		// in this case, a simple read may be sufficient
		// since the child send the whole msg in the same write,
		// but with a greater message size, even with a single write
		// the message may not be completely get in a signgle read
		while( (nr = read(p[0], child_msg + curr_pos, 16)) > 0) {
			printf("read bytes = %d\n", nr);
			curr_pos += nr;
		}
		
		printf("parent- child message is '%s'\n", child_msg);
		
		
	}
	return 0;
}
	
	
		
