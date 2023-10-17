/**
 * Build normally (without static linking)
 *  
 * Use /proc/meminfo to observe avaiable memory on waiting points
 * from child and parent. 
 * Note the COW (Copy on Write) semantics applied to .data region
 * 
 * Repeat observation using now the more detailed /proc/<parent_pid>/smaps
 * and /proc/<child_pid>/smaps, namely the Rss: line from both parent and child
 * at waiting points.
 */


#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>



#define DATA_SIZE (128*1024*1024)
#define VALS_SIZE (64*1024*1024)

uint8_t data[DATA_SIZE]  = { 4 };

uint8_t vals[VALS_SIZE];

void  susp_point(char *msg) {
	printf("%s: press return to  continue...", msg);
	getchar();
}


void fill_array(uint8_t a[], int start, int size, int val) {
	for(int i = start; i < size; ++i) {
		a[i] = val;
	}
}


long sum_array(uint8_t a[], int start, int size) {
	long sum = 0;
	for(int i=start; i < size; ++i) {
		sum += a[i];
	}
	return sum;
}


int main() {
	 
	printf("my pid is %d\n", getpid());
 	
	susp_point("on start");
	
	long res = sum_array(data, 0, DATA_SIZE/2);
	printf("data sum = %ld\n", res);
 	susp_point("after data sum");
    
    res = sum_array(vals, 0, VALS_SIZE);
	printf("vals sum = %ld\n", res);
	susp_point("after vals sum");
	 
	
	if (fork()==0) { // child
	 
		printf("child: my pid is %d\n", getpid());
		susp_point("child: on start");
		
		long res = sum_array(data, 0, DATA_SIZE/2);
		printf("child: data sum = %ld\n", res);
		susp_point("child: after data sum");
		
		fill_array(data, 0, DATA_SIZE/2, 1);
		susp_point("child: after data fill");
		
		fill_array(vals, 0, VALS_SIZE, 1);
		susp_point("child: after vals fill");
		exit(0);
	}
	
	wait(NULL);
	
	susp_point("parent: terminate");
	return 0;
}
