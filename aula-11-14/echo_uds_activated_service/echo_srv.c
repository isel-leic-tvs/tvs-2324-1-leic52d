/*
 * implements an echo server using unix domain stream sockets
 */

#include <systemd/sd-daemon.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/un.h>
#include <sys/socket.h>
#include "echo_service.h"

#include <syslog.h>
#include <signal.h>
#include <stdbool.h>
#include <pthread.h>
#include <stdlib.h>

// size of pending connections queue
#define BACKLOG 128

// globals
int srv_sock;
volatile bool interrupted = false;

void init_log() {
	//openlog("echod", LOG_PID, LOG_DAEMON);
}

void sigterm_handler(int sig) {
	interrupted = true;
	close(srv_sock);
}

void init() {
	// save daemon pid
#ifdef WITH_PIDFILE
	char pidfile[128];
	sprintf(pidfile, "echo %d > %sechod.pid",  getpid(), ECHO_DIR);
	system(pidfile); 
#endif

	init_log();
	
	//handling sigterm
	signal(SIGTERM, sigterm_handler);
}



void process_connection(int cfd) {
	echo_msg_t msg;
	int nread;
	
	while ((nread = read(cfd, &msg, sizeof(echo_msg_t))) > 0) {
		write(cfd, &msg, nread);
	}
	close(cfd);		 
}

void* dispatch_connection(void *arg) {
	int cfd = (int)(size_t) arg;
	process_connection(cfd);
	return NULL;
}


void run() {
	int cli_sock; // connection socket
	
	fprintf(stderr, "echo server started!\n");
	while (!interrupted) {  
		struct sockaddr_un cli_addr;
		socklen_t addrlen = sizeof(struct sockaddr_un);
		cli_sock = accept(srv_sock, (struct sockaddr *)  &cli_addr, &addrlen);
		if (interrupted) break;
		if (cli_sock == -1) {
			printf("error creating socket");
			break;
		}
	 	pthread_t cthread;
		pthread_create(&cthread, NULL, dispatch_connection, (void *) (size_t) cli_sock);
	 
	}
	fprintf(stderr, "echo server terminated!\n");
}

int main(int argc, char *argv[]) {
	
	init();
	
	
	int nfd = sd_listen_fds(0);
	
	if (nfd != 1) {
		fprintf(stderr, "echod: none or too many file descriptors\n");
		exit(1);
	}
 
	// server socket from systemd launcher
	srv_sock = SD_LISTEN_FDS_START;
	
	// run the server
	run();
	
	// cleanup

	close(srv_sock);
	closelog();
	
}


 
