#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "memchan.h"
#include "memutils.h"

/*
 * Create a generic synchronized fifo (ring buffer) in shared memory
 */
mem_channel_t *mc_create(int elem_size, int capacity, const char *name) {
	int mc_size = sizeof(mem_channel_t) + elem_size*capacity;
	mem_channel_t *mc;
		
	bool has_items_created = false, has_space_created = false;
	
	mc = (mem_channel_t *) shmem_create(name, mc_size); 
	
	pthread_mutexattr_t attr;
	pthread_mutexattr_init(&attr);
	pthread_mutexattr_setpshared(&attr, PTHREAD_PROCESS_SHARED /*shared between processes */);
	pthread_mutex_init(&mc->mutex, &attr);

	if (sem_init(&mc->has_items, true, 0) != 0) goto error;
	has_items_created = true;
	if (sem_init(&mc->has_space, true, capacity) != 0) goto error;
	has_space_created = true;
	mc->elem_size = elem_size;
	mc->capacity = capacity;
	mc->total_size = mc_size;
	mc->iget = mc->iput = 0;
	mc->ownerid = getpid();
	
	return mc;
error:
	if (mc == NULL) return NULL;
	if (has_space_created) sem_destroy(&mc->has_space);
	if (has_items_created) sem_destroy(&mc->has_items);
	shmem_destroy(name, mc, mc_size); 
	return NULL;
}

/*
 * Opens an existing synchronized ring buffer on shared memory
 */
mem_channel_t *mc_open(const char *name) {	
	return shmem_open(name);
}


bool mc_send(mem_channel_t *mc, void *item) {
	// wait for space avaiable
	sem_wait(&mc->has_space);
	
	// copy the value to buffer
	
	pthread_mutex_lock(&mc->mutex);
	
	memcpy(mc->buffer + mc->iput*mc->elem_size, item, mc->elem_size);
	mc->iput = (mc->iput + 1) % mc->capacity;
	
	pthread_mutex_unlock(&mc->mutex);
	// notify receivers
	sem_post(&mc->has_items);
	
	return true;
}

bool mc_rcv(mem_channel_t *mc, void *item_ptr) {
	// wait for items avaiable
	sem_wait(&mc->has_items);
	
	pthread_mutex_lock(&mc->mutex);
	size_t pos =  mc->iget;
	mc->iget = (mc->iget + 1) % mc->capacity;
	// copy the value to client buffer
	memcpy(item_ptr, mc->buffer + pos*mc->elem_size, mc->elem_size);
	pthread_mutex_unlock(&mc->mutex);
	// notify senders
	sem_post(&mc->has_space);
	return true;
}

void mc_destroy(mem_channel_t *mc, const char *name) {
	if (mc == NULL) return;
	if (mc->ownerid != getpid()) {
		munmap(mc, mc->total_size);
		return;
	}
	sem_destroy(&mc->has_space);
	sem_destroy(&mc->has_items);
	pthread_mutex_destroy(&mc->mutex);
	shmem_destroy(name, mc, mc->total_size);
}
