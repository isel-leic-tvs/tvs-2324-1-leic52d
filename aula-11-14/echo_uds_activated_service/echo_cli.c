/*
 * implements an echo client using a unix domain stream socket
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/un.h>
#include <sys/socket.h>

#include "../utils/chrono.h"
#include "echo_service.h"
 
#define NITERS 1000
#define SHOW_RESP

int create_client_socket() {
	return socket(AF_UNIX, SOCK_STREAM, 0);
}


int main(int argc, char *argv[]) {
	 
	
	int cli_sock = create_client_socket();
 	
	if (cli_sock < 0) {
		fprintf(stderr, "error creating socket\n");
		return 1;
	}
	
	/* Construct server address, and make the connection */
	struct sockaddr_un srv_address;
	
	memset(&srv_address, 0, sizeof(struct sockaddr_un));
	srv_address.sun_family = AF_UNIX;
	strncpy(srv_address.sun_path, ECHO_SOCKET_NAME, 
			sizeof(srv_address.sun_path) - 1);
	
	if (connect(cli_sock, (struct sockaddr *) &srv_address, 
	          sizeof(struct sockaddr_un)) == -1) {
		fprintf(stderr, "Error connecting socket\n");
		return 2;
	}
	
	echo_msg_t msg, resp;
	int pid  = getpid();
	
	chrono_t chron = chrono_start();
	 

	for(int try=1; try <= NITERS; try++) {
		sprintf(msg.msg, "Hello_%d_%d", pid, try);
		write(cli_sock, &msg, strlen(msg.msg)+1);
		// get response
		read(cli_sock, &resp, sizeof(echo_msg_t));
#ifdef SHOW_RESP
		printf("%s\n", resp.msg);
#endif
	}
	
	printf("%d tries in %ld micros!\n", NITERS, chrono_micros(chron));
	
	printf("press return to continue..."); getchar();
	close(cli_sock);

	printf("client done!\n");
	return 0;
}
