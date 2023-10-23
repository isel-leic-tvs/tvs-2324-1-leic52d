/**
 * for the most curious
 * this program load errno  with an eror code received from input
 * and show the respective error description via perror
 * 
 * 
 * Try to understand what is happening here... 
 */

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
 

int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("usage: errno <num>\n");
		return 1;
	}
	
	errno = atoi(argv[1]);
	perror("error");
	
	return 0;
}
