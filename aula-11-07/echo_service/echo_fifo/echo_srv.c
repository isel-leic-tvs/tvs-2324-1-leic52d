/*
 * implements an echo server using a FIFO (named pipe) channel
 */

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>

#include "echo_service.h"


#define MAX_MSGS	1024


int create_fifo(const char *name) {
	int fd; // fifo file descriptor
 
	int res = mkfifo(name, 0622 /* read/write permission for owner, write for others */);
	
	if (res == -1 && errno != EEXIST) return -1;
	
	if (signal(SIGPIPE, SIG_IGN) == SIG_ERR) return 1;
	
	// In general opening a fifo for read/write is not supported (just read or write only)
	// this is specific for some unix variants including Linux and greatly simplifies the FIFO management
	// since there is no blocking in open and read remains blocked  even in the absence of other writers
	if ( (fd = open(name, O_RDWR)) == -1) 
		return -1;
	
	printf("server:creation done!\n");
	return fd;
}

static int open_client_fifo(int client_id) {
	char resp_name[CHANNEL_NAME_MAX_SIZE];
	snprintf(resp_name, CHANNEL_NAME_MAX_SIZE, "%s%d", ECHO_CLIENT_PREFIX, client_id);
	return open(resp_name, O_WRONLY);
}

void run(int fifo_fd) {
	for(; ; ) {
		echo_msg_t msg;
		read(fifo_fd, &msg, sizeof(echo_msg_t));
		
		
		// send response
		char client_name[CHANNEL_NAME_MAX_SIZE];
		snprintf(client_name, CHANNEL_NAME_MAX_SIZE, "%s%d", ECHO_CLIENT_PREFIX, msg.sender);
		int cfd = open_client_fifo(msg.sender);
		if (cfd == -1) {
			fprintf(stderr, "error opening client channel %s\n", client_name);
			break;
		}
		write(cfd, &msg, sizeof(echo_msg_t)); 	
		close(cfd);
		
		 
	}
}

int main(int argc, char *argv[]) {
	
	int fifo_fd = create_fifo(ECHO_SERVICE_NAME);
 
	if (fifo_fd == -1) {
		fprintf(stderr, "error creating fifo channel\n");
		return 1;
	}
	
 	run(fifo_fd);
	
	close(fifo_fd);
	 
	printf("server done!\n");
	return 0;
}
