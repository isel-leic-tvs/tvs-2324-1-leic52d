/**
 * Este programa apresenta os endereços de funções e variáveis globais
 * associadas a diferentes secções do executável
 * 
 * Em geral o Linux usa, por razões de segurança, randomização de endereços, 
 * pelo que diferentes execuções do programa produzirão diferentes resultados.
 * 
 * Para inibir a randomização, execute o comando:
 *   	sudo sh -c "echo 0 > /proc/sys/kernel/randomize_va_space"
 * 
 * Execute em duas consolas duas instâncias do programa avançando
 * alternadamente e observe os resultados
 * 
 * Para repor a randomização execute o comando:
 * 		sudo sh -c "echo 2 > /proc/sys/kernel/randomize_va_space"
 */

#include <stdio.h>
#include <stdlib.h>

int global = 5;

char letters[1024];

const int value = 5;


int main(int argc, char *argv[]) {
	int local = 2;
	
	printf("&main=%p\n", main);
	printf("&global=%p\n", &global);
	printf("&letters=%p\n", letters);
	printf("&value=%p\n", &value);
	printf("&local=%p\n", &local);
	
	printf("before change global is %d\n", global);
	printf("press enter to continue");
	getchar();
	if (argc == 2) {
		global = atoi(argv[1]);
	}
	printf("after change global is %d\n", global);
	printf("press enter to continue");
	getchar();
	 
	return 0;
	
}
