/**----------------------------------------------
 * utilização ds "mmap"
 * para criar um ficheiro binário de inteiros de 1 a NUMBERS_COUNT
 * 
 * JMartins, outubro de 2022
 */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include "filespecs.h"



int main(int argc, char *argv[]) {
	 
	const int FILE_SIZE = NUMBERS_COUNT*sizeof(int);

	int fd = open(INTS_FILENAME, O_CREAT | O_TRUNC | O_RDWR, 0666);
		
	if (fd < 0) {
		perror("error creating numbers file");
		return 1;
	}
	
	// Força a dimensão do ficheiro para o mapeamento
	if (ftruncate(fd, FILE_SIZE ) == -1) {
		perror("error setting file size");
		return 2;
	}
	
	void *mapbase = mmap(NULL, FILE_SIZE, PROT_WRITE, MAP_SHARED, fd,0);
	if (mapbase == MAP_FAILED) {
		perror("error mapping numbers file");
		return 3;
	}
	
	// o descritor já não é necessário após o mapeamento
	close(fd);
	
	// ver a região com um array de inteiros
	int *ints = (int *) mapbase;
	
	for(int i=0; i < NUMBERS_COUNT; ++i) {
		printf("i=%d\n", i);
		ints[i] = i;
	}
	
	
	if (munmap(mapbase, FILE_SIZE) == -1) {
		perror("error unmapping numbers file");
		return 4;
	}
	
	return 0;
}
