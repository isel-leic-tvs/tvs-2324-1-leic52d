#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

/**
 * In order to distinguish parent from chils executions,
 * fork return different values to both:
 * To the parent is returned the child process id (pid) 
 * and to the child is returned 0 (not a valid id)
 * 
 * The code below show this
 * 
 * Uncomment the  DELAYED_WAIT define and note (using command "ps -ax")
 * that lists all the existing processes,
 * that the child process remains (with state Defunct) while parent is suspended
 * 
 */

// #define DELAYED_WAIT


int main() {
	
	
	printf("parent pid: %d\n", getpid());
	
	int pchild = fork();
	
	if (pchild == -1) {
		perror("Error on fork");
	}
	else if (pchild == 0) {
		printf("child pid (on child) = %d\n", getpid());
	
		exit(0);
	}
	else {
		printf("child pid (on parent) = %d\n", pchild);
	}
	
#ifdef DELAYED_WAIT
	sleep(20); // 20 seconds
#endif
	
	waitpid(pchild, NULL, 0); // <=> wait(NULL);
	
	printf("process child terminate!\n");
	
	return 0;
}
