#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

/**
 * The code below aim to show that,
 * although the child memory state on start 
 * is equal on parent when fork is called,
 * changes in parent or child are not reflected in the other process.
 * 
 * Note that does not mean that the memory state is really copied 
 * from parent to child, as we will see in future lectures.
 */


int global = 30;

int main() {
	int local = 10;
	
	printf("parent pid: %d\n", getpid());
	
	printf("on parent, global=%d\n", global);
	printf("on parent, local=%d\n", local);
		
	int pchild = fork();
	
	if (pchild == -1) {
		perror("Error on fork");
	}
	else if (pchild == 0) {
		printf("child pid (on child) = %d\n", getpid());
		
	
		sleep(5);
		
		printf("on child, global=%d\n", global);
		printf("on child, local=%d\n", local);
		global = 50;
		local = 0;
		exit(0);
	}
	else {
		printf("child pid (on parent) = %d\n", pchild);
	}
	
	local = 100;
	global = 200;
	
	waitpid(pchild, NULL, 0); // <=> wait(NULL);
	
	printf("process child terminate!\n");
	
	printf("on parent, global=%d\n", global);
	printf("on parent, local=%d\n", local);
	
	 
	return 0;
}
