
#ifndef _MEM_UTILS_H
#define _MEM_UTILS_H

#include <sys/types.h>
#include <sys/mman.h>



/**
 * Create a shared memory region of a specific size
 * 
 * arguments:
 * 		the name(path) and size of shared memory 
 * returns:
 * 		the address of the shared memory region in the process or
 *  	NULL in case of error
 */
void *shmem_create(const char *path, size_t size);


/**
 * Open a shared memory region of a specific size
 * 
 * arguments:
 * 		the name(path) and size of shared memory 
 * returns:
 * 		the address of the shared memory region in the process or
 *  	NULL in case of error
 */
void *shmem_open(const char *path);

 

void shmem_destroy(const char *name, void *base, size_t size);

  

#endif
