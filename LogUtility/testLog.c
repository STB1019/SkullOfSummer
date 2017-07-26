#include <stdio.h>
#include <unistd.h>
#include "log.h"

int add_2_numbers(int a, int b) {
	debug("numbers are a=%d b=%d", a, b);
	return a + b;
}


int main() {

	critical("Starting program...");
	for (int i=0; i<4; i++) {
		info("first number is %d", i);
		sleep(1);
		for (int j=0; j<10; j++) {			
			printf("sum is %d\n", add_2_numbers(i, j));
		}
	}
	critical("Program terminated");
}
