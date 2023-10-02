all : usewrite

CFLAGS=-g -Wall

mywrite.o: mywrite.s
	gcc -c  mywrite.s
	
usewrite: usewrite.c mywrite.o
	gcc -o usewrite $(CFLAGS) usewrite.c mywrite.o

clean:
	rm -rf *.o usewrite hello_pthreads
