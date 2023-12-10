#include <stdio.h>
#include <unistd.h>

int main() {
    printf("Hello from process %d in container\n", getpid());
    return 0;
}

