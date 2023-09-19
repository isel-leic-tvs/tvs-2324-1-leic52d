#include <stdio.h>
#include <stdlib.h>

#include <fcntl.h>
#include <unistd.h>

/**
 * Este programa abre duas vezes o mesmo ficheiro
 * realizando escritos a partir dos dois descrtores obtidos.
 * Observe o resultado.
 * Note que a ordem de aberturas e fechos não é relevante,
 * apenas a ordem de escritas enquanto os dois descitores estão activos
 */

#define FILENAME "xx"

int main() {
	int fd = open(FILENAME, O_CREAT | O_TRUNC | O_WRONLY, 0664);
	if (fd == -1) {
		perror("error opening file xx");
		exit(1);
	}
	if (write(fd, "1234", 4) == -1) {
		perror("error writing file xx");
		exit(1);
	}

	int fd2 = open(FILENAME, O_WRONLY, 0664);
	
	if (fd2 == -1) {
		perror("error opening file xx");
		exit(1);
	}
	if (write(fd2, "5678", 4) == -1) {
		perror("error writing file xx");
		exit(1);
	}
	printf("sucesso!\n");
	
	close(fd);
	close(fd2);
		
	return 0;
	
}
