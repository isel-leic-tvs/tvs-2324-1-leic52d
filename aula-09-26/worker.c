#include <stdio.h>
#include <unistd.h>

int main() {
	int nstep = 1;
	
	while (nstep < 100) {
		sleep(5);
		printf("step %d\n", nstep++);
	}
	
	return 0;
}
