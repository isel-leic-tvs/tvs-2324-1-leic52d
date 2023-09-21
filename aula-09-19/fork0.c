/**
 * First example for creating a new process
 * 
 * "fork" is the Linux(Unix) API operation that
 * creates a new process, that is almost a pefect copy
 * of his parent. The memory state, the execution state, 
 * the active file descriptors, the environment variables, 
 * the current directory and other process state remains
 * equal in the child.
 * Of course, the process identifier and some statistic state,
 * as execution times, are different in the child.
 * 
 * As the execution state is the same in child, including the
 * Instruction Pointer (aka Program Counter), this means that 
 * both processes, parent and child, will execute the same code 
 * after fork return.
 * 
 * This explains the output of next program.
 *
 * 
 */


#include <stdio.h>
#include <unistd.h>


int main() {
	printf("parent process is %d\n", getpid());
	
	fork();
	
	printf("my process id is %d\n", getpid());
	
	return 0;
}
