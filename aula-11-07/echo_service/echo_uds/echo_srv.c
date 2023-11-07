/*
 * implements an echo server using unix domain stream sockets
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/un.h>
#include <sys/socket.h>
#include "echo_service.h"
#include <pthread.h>
 
// size of pending connections queue
#define BACKLOG 5


int create_bind_socket(const char* sock_name) {
	int sock;
	struct sockaddr_un srv_addr;
	sock = socket(AF_UNIX, SOCK_STREAM, 0);
	if (sock == -1) return -1;
	
	// remove old entry if exists
	if (unlink(sock_name) == -1 && errno != ENOENT) {
		close(sock);
		return -2;
	}
		 
		
	/*  bind socket */
	memset(&srv_addr, 0, sizeof(struct sockaddr_un));
	srv_addr.sun_family = AF_UNIX;
	strncpy(srv_addr.sun_path, sock_name, sizeof(srv_addr.sun_path) - 1);
	
	if (bind(sock, (struct sockaddr *) &srv_addr, 
	               sizeof(struct sockaddr_un)) == -1) {
		close(sock);
		return -3;
	}
	
	return sock;
}


void process_connection(int cfd) {
	echo_msg_t msg;
	int nread;
	
	while ((nread = read(cfd, &msg, sizeof(echo_msg_t))) == sizeof(echo_msg_t)) {
		write(cfd, &msg, sizeof(echo_msg_t));
	}
	close(cfd);	

}

void* dispatch_connection(void *arg) {
	int cli_sock = (int)(size_t) arg;
	process_connection(cli_sock);
	return NULL;
}

void run(int srv_sock) {
	int cli_sock; // connection socket
	for (;;) {  
	
		cli_sock = accept(srv_sock, NULL, NULL);
		if (cli_sock == -1) {
			fprintf(stderr, "error creating socket\n");
			return;
		}
		
		 
	 
		pthread_t cthread;
		pthread_create(&cthread, NULL, 
		      dispatch_connection, (void *) (size_t) cli_sock);
		 
	 
		//process_connection(cli_sock);
 	 
	}
}

int main(int argc, char *argv[]) {
	int srv_sock;
	
	// create server socket
	if ((srv_sock = create_bind_socket(ECHO_SERVICE_NAME)) < 0) {
		fprintf(stderr, "error creating socket\n");
		return 1;
	}
 
    // set listen queue size
	if (listen(srv_sock, BACKLOG) == -1) {
		fprintf(stderr, "error setting  listen queue size\n");
		return 1;
	}
	
	// run the server
	run(srv_sock);
	
	unlink(ECHO_SERVICE_NAME);
	close(srv_sock);
}


 
