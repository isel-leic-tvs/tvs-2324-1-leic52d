#include <stdio.h>
#include <unistd.h>


/**
 * "execlp" is an Linux API operation from "exec" family
 * it receives a filename supposedly executable, 
 * and multiple strings (NULL terminated) that correspond to
 * the program arguments.
 * 
 * "execlp" find the executable on folders refered to PATH environment variable, 
 * and in case of success it changes the code and data of current process to
 * that program. So the "exelp" (as well as other "exec" family operations) never
 * returns to caller in case of success (just on error).
 * 
 * While the program below is executing check the list of processes (using ps -ax)
 * where you will find and execution of "cat" command (note the procees id)
 * 
 * To terminate cat execution use the key combination CTRL D
 *
 */
 
int main() {
	
	printf("my pid is %d\n", getpid());
	
	execlp("cat", "cat", NULL);
	
	printf("my pid is %d\n", getpid());
	
	return 0;
}
