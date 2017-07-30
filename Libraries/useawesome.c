#include <stdio.h>

#include <stdbool.h>

int main() {
	char buffer[100];
	int a, b;

	printf("choose first number: ");
	if (fgets(buffer, 100, stdin)) {
		sscanf(buffer, "%d", &a);
	}

	printf("choose second number: ");
	if (fgets(buffer, 100, stdin)) {
		sscanf(buffer, "%d", &b);
	}

	printf("a random number between %d and %d is %d\n", a, b, randRange(a, b, true, true));
}
