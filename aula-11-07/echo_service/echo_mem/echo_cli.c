/*
 * implements an echo server using a ring buffer based memory channel
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "memchan.h"
#include "echo_service.h"
#include "../utils/chrono.h"
 
#define MAX_MSGS	1
#define NITERS 1000

//#define SHOW_RESP

int main(int argc, char *argv[]) {
	 
	
	mem_channel_t *channel = mc_open(ECHO_SERVICE_NAME);
	if (channel == NULL) {
		fprintf(stderr, "error opening server channel\n");
		return 1;
	}
	
	// create response channel
	char resp_channel_name[CHANNEL_NAME_MAX_SIZE];
	snprintf(resp_channel_name, CHANNEL_NAME_MAX_SIZE, "%s%d", ECHO_CLIENT_PREFIX, getpid());
	mem_channel_t *resp_channel = mc_create(sizeof(echo_msg_t), 1, resp_channel_name);
	if (channel == NULL) 
		fprintf(stderr, "error creating response channel\n");
	else {	
		
		echo_msg_t msg, resp;
		
		msg.sender = getpid();
		
		chrono_t chron = chrono_start();
		for(int try = 1; try <= NITERS; try++) {
			sprintf(msg.msg, "Hello_%d_%d", msg.sender, try);
			mc_send(channel, &msg);
			// get response
			mc_rcv(resp_channel, &resp);
#ifdef SHOW_RESP
			printf("%s\n", resp.msg);
#endif
		}
		
		printf("%d tries in %ld micros!\n", NITERS, chrono_micros(chron));

	}
	 
 
	mc_destroy(resp_channel, resp_channel_name );
	mc_destroy(channel, ECHO_SERVICE_NAME);
	
	printf("client done!\n");
	return 0;
}
