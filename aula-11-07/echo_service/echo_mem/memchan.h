#pragma once

#include <sys/types.h>

#include <semaphore.h>
#include <pthread.h>
#include <stdbool.h>

#define CHANNEL_NAME_MAX_SIZE 128

typedef unsigned char byte;

typedef struct {
	pid_t ownerid;			// the creator process
	sem_t has_items;		// signal items avaiable
	sem_t has_space;		// signals space avaiable
	pthread_mutex_t mutex;	// lock provider
	int elem_size;			// size of each fifo element
	int capacity;			// fifo capacity
	int total_size;			// shared region size
	size_t iget;			// receive index
	size_t iput;			// send index
	byte buffer[1];			// start of the buffer
} mem_channel_t;



/**
 * Create a generic synchronized ring buffer in private or shared memory
 */
mem_channel_t *mc_create(int elem_size, int capacity, const char *name);
	 

/**
 * Opens an existing synchronized ring buffer on shared memory
 */
mem_channel_t *mc_open(const char *name);
	 

bool mc_send(mem_channel_t *rb, void *item);
	 

/**
 * receives an "item" from memory channel.
 * blocks the "caller" while none exists
 */
bool mc_rcv(mem_channel_t *rb, void *item_ptr);
	

void mc_destroy(mem_channel_t *rb, const char *name);
 
