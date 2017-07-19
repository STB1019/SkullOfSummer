#include <stdio.h>

int fInline(int a, int b) {
	return a + b;
}

int main() {

	int a = 7;
	int b = 42;
	int c = fInline(a, b);
	printf("%d\n", c);
}
