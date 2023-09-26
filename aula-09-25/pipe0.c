#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

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
		
		close(p[1]); // o descritor que permite escrita não é necessário no filho
		
		char child_msg[MAX_MSG_SIZE];
		int curr_pos = 0; // posição onde colocar os bytes
		int nr;           // bytes lidos pelo read
		
		
		
		waitpid(pchild, NULL, 0); // wait for child termination
		
		
		while( (nr = read(p[0], child_msg + curr_pos, 16)) > 0) {
			printf("read bytes = %d\n", nr);
			curr_pos += nr;
		}
		
		printf("parent- child message is '%s'\n", child_msg);
		
		
	}
	return 0;
}
	
	
		
