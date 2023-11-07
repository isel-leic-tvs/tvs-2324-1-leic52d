/**
 * memory waster for swaping activity observation
 * with /proc/meminfo
 */

#include <stdio.h>
#include <errno.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdint.h>

#define REG_SIZE (1024*1024*400)
#define PAGE_SIZE 4096

typedef uint8_t byte;

void  susp_point(char *msg) {
	printf("%s: press return to  continue...", msg);
	getchar();
}

void* map_region(size_t size) {
	return mmap(NULL, size, PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
}

int sum_first_byte_pages(byte* data, int size) {
	int sum = 0;
	for(int i=0; i < size; i+= PAGE_SIZE) {
		sum += data[i];
	}
	return sum;
}

void fill_data(byte* data, int size, int val) {
	for(int i=0; i < size; i += PAGE_SIZE) {
		data[i] = val;
	}
}


int main(int argc, char *argv[]) {
	void *mapbase;
	
	bool writer = (argc == 2);
	
	while(true) {
		if ((mapbase=map_region(REG_SIZE)) == MAP_FAILED) {
			perror("mapping error");
			return 1;
		}
		
		if (writer) {
			fill_data(mapbase, REG_SIZE, 1);
			susp_point("after region modification");
		}
		else {
			printf("sum_first_byte_pages=%d\n", sum_first_byte_pages((byte *) mapbase, REG_SIZE));
			susp_point("after region access");
		}
		
	}
	 	
	return 0;
}
