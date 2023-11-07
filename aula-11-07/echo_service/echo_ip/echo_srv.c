/*
 * implements an echo server using ip domain stream sockets
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

 
#include <arpa/inet.h>
#include <sys/socket.h>

#include "echo_service.h"
#include <pthread.h>
 
 
// size of pending connections queue
#define BACKLOG 1024



int create_bind_server_socket(const char* ip_addr, int port) {
	int sock;
	struct sockaddr_in srv_addr;
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1) return -1;
	
 
	/*  bind socket */
	bzero(&srv_addr, sizeof(struct sockaddr_in));
	srv_addr.sin_family = AF_INET;
	srv_addr.sin_addr.s_addr = inet_addr("0.0.0.0"); // inet_addr(ip_addr);
	srv_addr.sin_port = htons(port);
	
	if (bind(sock, (struct sockaddr *) &srv_addr, sizeof(struct sockaddr_in)) == -1) {
		close(sock);
		return -3;
	}
	
	return sock;
}

void process_connection(int cli_sock) {
	echo_msg_t msg;
	int nread;
	
	while ((nread = read(cli_sock, &msg, sizeof(echo_msg_t))) == sizeof(echo_msg_t)) {
		write(cli_sock, &msg, sizeof(echo_msg_t));
	}
	close(cli_sock);	
		 
}

void* dispatch_connection(void *arg) {
	int cli_sock = (int)(size_t) arg;
	process_connection(cli_sock);
	return NULL;
}

void run(int srv_sock) {
	int cli_sock; // connection socket
	
	printf("server started!\n");
	for (;;) {  
		struct sockaddr_in cli_addr;
		socklen_t addrlen = sizeof(struct sockaddr_in);
		cli_sock = accept(srv_sock, (struct sockaddr *)  &cli_addr, &addrlen);
		if (cli_sock == -1) {
			fprintf(stderr, "error creating socket\n");
			return;
		}
		printf("connected with %x, port %d...\n", cli_addr.sin_addr.s_addr, cli_addr.sin_port);
		
		
		pthread_t cthread;
		pthread_create(&cthread, NULL, 
		      dispatch_connection, (void *) (size_t) cli_sock);
	  
	    //process_connection(cli_sock);
		  
	}
}

int main(int argc, char *argv[]) {
	int srv_sock;
	
	
	// create server socket
	if ((srv_sock = create_bind_server_socket(ECHO_SERVER_ADDR, ECHO_SERVER_PORT)) < 0) {
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
	
	 
	close(srv_sock);
}


 
