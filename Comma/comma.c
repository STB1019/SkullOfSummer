#include <stdio.h>

int main() {
	int a = 5;
	int b = 3; 
	printf("a=%d b=%d comma operator=%d \n", a, b, (a += 2, b, a + b));
}
