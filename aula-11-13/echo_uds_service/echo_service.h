#pragma once

#define ECHO_DIR	"/opt/echod/"

#define ECHO_SOCKET_NAME ECHO_DIR "echod.sock"



#define MAX_MSG_SIZE 256


typedef struct  {
	char msg[MAX_MSG_SIZE];
} echo_msg_t;

 
