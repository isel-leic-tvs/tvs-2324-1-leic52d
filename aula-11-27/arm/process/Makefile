.PHONY: all clean

all: hello_arm64

hello_arm64: hello_arm64.o
	aarch64-linux-gnu-ld -o hello_arm64 hello_arm64.o

hello_arm64.o: hello_arm64.s
	aarch64-linux-gnu-as -o hello_arm64.o hello_arm64.s

clean:
	rm -f hello_arm64.o hello_arm64

