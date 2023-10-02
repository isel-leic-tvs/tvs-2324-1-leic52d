#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
 
/**
 * this program tests the implementation
 * of our version of system call write (my_write)
 */
 
 
int my_write(int fd, const void *buf, int size);


// this fuction as the sole purpose of getting a fd that is free
// in order to check an error situation on our write call
int first_unused_fd() {
	int fd = 0;
	while (fcntl(fd, F_GETFD) == 0) fd++;
	return fd;
}




int main() {
	//int fd = first_unused_fd();
	
	
	// uncomment previous line and change STDOUT_FILENO with fd value
	// and check the result
	// Compare with original write use
	int nw = my_write(STDOUT_FILENO, "hello again!\n", 13);
	if (nw == -1) {
		char msg[256];
		snprintf(msg, 256, "error writing on fd %d", STDOUT_FILENO);
		perror(msg);
	}
	else {
		printf("%d bytes written!\n", nw);
	}
	return 0;
}














 
