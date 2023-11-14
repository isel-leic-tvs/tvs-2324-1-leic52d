BIN = bin

UTILS = ../utils
INCLUDES = -I $(UTILS)

CC = gcc


CFLAGS = -g -Wall

ECHO_SRV_SRCS = echo_srv.c 
 
ECHO_CLI_SRCS = echo_cli.c  $(UTILS)/chrono.c
 

 
all: echod echo_cli  

echod:	$(ECHO_SRV_SRCS)
	$(CC) -o echod $(CFLAGS) $(ECHO_SRV_SRCS)  
	
echo_cli:	$(ECHO_CLI_SRCS)
	$(CC) -o echo_cli  $(CFLAGS) $(ECHO_CLI_SRCS)  
 
install:
	sudo ./install.sh

uninstall:
	sudo ./uninstall.sh

clean:
	rm -rf *.o echo_cli echod
	
