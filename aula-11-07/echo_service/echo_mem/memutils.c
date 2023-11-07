
#include "unistd.h"
#include <sys/stat.h>

#include <fcntl.h>
#include "memutils.h"

/**
 * utils
 */
 
 
static void *shmem_internal_map(int fd, size_t size) {
	void *base = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	close(fd);
	
	if (base == MAP_FAILED /* (void*) -1 */ ) {
		return NULL;
	}
	
	return base;
}


/**
 * create a shared memory region of a specific size
 * 
 * arguments:
 * 		the name(path) and size of shared memory 
 * returns:
 * 		the address of the shared memory region in the process or
 *  	NULL in case of error
 */
void * shmem_create(const char *path, size_t size) {
	int fd = shm_open(path, O_CREAT | O_RDWR, 0666);
	 
	if (fd == -1) return NULL;
	if (ftruncate(fd, size) == -1) {
		close(fd);
		return NULL;
	}
	
	return shmem_internal_map(fd, size);
 					
}

/**
 * opens a shared memory region of a specific size
 * 
 * arguments:
 * 		the name(path) and size of shared memory 
 * returns:
 * 		the address of the shared memory region in the process or
 *  	NULL in case of error
 */
void *shmem_open(const char *path) {
	
	int fd = shm_open(path, O_RDWR, 0666);
	struct stat statbuf;
	
	if (fd == -1) return NULL;
	if (fstat(fd, &statbuf) != 0) {
		close(fd);
		return NULL;
	}
	
	return shmem_internal_map(fd, statbuf.st_size);	
}



void shmem_destroy(const char *name, void *base, size_t size) {
	munmap(base, size);
	unlink(name);
}

 
 
