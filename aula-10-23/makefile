all: shreg reader writer libmath.so errno client client_dyn  

CFLAGS= -g -Wall 

shreg: shreg.c
	gcc -o shreg $(CFLAGS) shreg.c
	
reader: reader.c
	gcc -o reader $(CFLAGS) reader.c

writer: writer.c
	gcc -o writer $(CFLAGS) writer.c
	
errno: errno.c
	gcc -o errno $(CFLAGS) errno.c
	
libmath.so: math.c
	gcc -o libmath.so $(CFLAGS) -fpic math.c -shared
		
client: client.c
	#gcc -o client $(CFLAGS) client.c '-Wl,-rpath,$$ORIGIN/.' libmath.so
	gcc -o client $(CFLAGS) client.c  libmath.so


client_dyn: client_dyn.c
	gcc -o client_dyn $(CFLAGS) client_dyn.c

	
clean:
	rm -rf reader writer libmath.so errno client client_dyn waster

prepare:
	sudo sh -c "echo /usr/local/lib  > /etc/ld.so.conf.d/tvs.conf"
	sudo ldconfig
	
install:
	sudo cp libmath.so /usr/local/bin
	
