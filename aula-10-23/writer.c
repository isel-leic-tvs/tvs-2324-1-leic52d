/**
 * the writer for example of named shared memory use via shm_open
 * 
 * observe smaps and shm object in /dev/shm
 */


#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include "shmem_defs.h"	

void  susp_point(char *msg) {
	printf("%s: press return to  continue...", msg);
	getchar();
}

int main(int argc, char *argv[]) {
	 
	printf("my pid is %d\n", getpid());
 
	susp_point("start point");
    int fd = shm_open(SHMEM_NAME, O_CREAT | O_RDWR, 0644);
    if (fd == -1) {
		perror("error creating shared mem object");
		return 1;
	}
	
	if (ftruncate(fd, SHMEM_SIZE) == -1) {
		perror("error truncating file!");
		close(fd);
		return 2;
	}
	
	void *mapbase = mmap(NULL, SHMEM_SIZE, PROT_WRITE | PROT_READ, MAP_SHARED, fd, 0);
	
	if (mapbase == MAP_FAILED) {
		perror("error mapping numbers file");
		return 3;
	}
	
	printf("memory mapped at %p\n", mapbase);
	susp_point("after file map");
	
	close(fd);
	
	int *ints = (int *) mapbase;
    ints[0] = 5;
    printf("memory first value setted: %d\n",  ints[0]);
	
	susp_point("after set value ");
	
	munmap(mapbase, SHMEM_SIZE);
	
	susp_point("after unmap shm region");
	return 0;
}
