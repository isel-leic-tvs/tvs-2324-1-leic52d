BIN = bin

UTILS = ../utils
INCLUDES = -I $(UTILS)

CC = gcc


CFLAGS = -g -Wall

ECHO_SRV_SRCS = echo_srv.c 
 
ECHO_CLI_SRCS = echo_cli.c  $(UTILS)/chrono.c
 

 
all: echod_auto echo_cli  

echod_auto:	$(ECHO_SRV_SRCS)
	$(CC) -o echod_auto $(CFLAGS) $(ECHO_SRV_SRCS) -lsystemd 
	
echo_cli:	$(ECHO_CLI_SRCS)
	$(CC) -o echo_cli  $(CFLAGS) $(ECHO_CLI_SRCS)  
 
install:
	./install.sh

uninstall:
	./uninstall.sh

clean:
	rm -rf *.o echo_cli echod_auto
	
