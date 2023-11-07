BIN = bin

UTILS = ../utils
INCLUDES = -I $(UTILS)

CC = gcc


CFLAGS = -g -Wall

ECHO_SRV_SRCS = echo_srv.c memchan.c memutils.c 
 
ECHO_CLI_SRCS = echo_cli.c memchan.c memutils.c $(UTILS)/chrono.c
 

 
all: echo_srv echo_cli  

echo_srv:	$(ECHO_SRV_SRCS)
	$(CC) -o echo_srv  $(ECHO_SRV_SRCS) -pthread 
	
echo_cli:	$(ECHO_CLI_SRCS)
	$(CC) -o echo_cli  $(ECHO_CLI_SRCS) -pthread 
 

# Compile rule	
.c.o:
	$(CC)  $(CFLAGS) $(INCLUDES) -c $< 
	

clean:
	rm -rf *.o echo_cli echo_srv
	
