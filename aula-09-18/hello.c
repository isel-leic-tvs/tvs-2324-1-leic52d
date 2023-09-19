#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


/**
 * Execute este programa com o define seguinte comentado e 
 * descomentado e explique a diferença de comportamento
 */

//#define TEMPLATE_AS_POINTER


#ifdef TEMPLATE_AS_POINTER
char *TEMPLATE_MSG = "hello to class %s\n";
#else
char TEMPLATE_MSG[] = "hello to class %s\n";
#endif

void to_upper(char *text) {
	while(*text != 0) {
		*text = toupper(*text);
		text++;
	}
}


int main(int argc, char*argv[]) {
	
	if (argc != 2) {
		printf("usage: hello <classname>\n");
		exit(0);
	}
	
	to_upper(argv[1]);
	TEMPLATE_MSG[0] = toupper(TEMPLATE_MSG[0]);
	printf(TEMPLATE_MSG, argv[1]);
	return 0;
}
