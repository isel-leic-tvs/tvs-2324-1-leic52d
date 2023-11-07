BIN = bin

UTILS = ../utils
INCLUDES = -I $(UTILS)

CC = gcc


CFLAGS = -g -Wall

ECHO_SRV_SRCS = echo_srv.c 
 
ECHO_CLI_SRCS = echo_cli.c  $(UTILS)/chrono.c
 

 
all: echo_srv echo_cli  

echo_srv:	$(ECHO_SRV_SRCS)
	$(CC) -o echo_srv $(CFLAGS) $(ECHO_SRV_SRCS)  
	
echo_cli:	$(ECHO_CLI_SRCS)
	$(CC) -o echo_cli  $(CFLAGS) $(ECHO_CLI_SRCS)  
 


clean:
	rm -rf *.o echo_cli echo_srv
	
