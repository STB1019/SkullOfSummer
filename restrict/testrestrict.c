#ifdef USERESTRICT
#	define restrict restrict
#else
#	define restrict
#endif

//reference: https://stackoverflow.com/a/30828422/1887602
//you need to put O3

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define TYPE long long
#define STYPE "long long"

#define SIZE 100000

long int getTimeInNanos(struct timespec t) {
	return t.tv_sec * 1000000000 + t.tv_nsec;
}

long int getSeconds(long int t) {
	return t / 1000000000;
}

long int getMilli(long int t) {
	return (t % 1000000000) / 1000000;
}

long int getMicro(long int t) {
	return (t % 1000000) / 1000;
}

void fr(TYPE *restrict a, TYPE *restrict b, TYPE *restrict x) {
  *a += *x;
  *b += *x;
}

int main(int argc, const char* args[]) {
	TYPE a;
	TYPE b;
	TYPE c;
	long int start;
	long int end;
	long int duration;

	if (argc != 2) {
		printf("help: ./program <non_negative_number>\n");
		printf("size of %s: %ld\n", STYPE, sizeof(TYPE));
		exit(1);
	}
	int exp = atoi(args[1]);
	long long iterations = 1 << exp;
	printf("iterations are %lld\n", iterations);

	a = 0;
	b = 0;
	c = 2;

	struct timespec nanos;
	clock_gettime(CLOCK_MONOTONIC, &nanos);
	start = getTimeInNanos(nanos);

	for (unsigned long long i=0; i<iterations; i++) {
		for (unsigned long long j=0; j<iterations; j++) {
			for (unsigned long long k=0; k<iterations; k++) {
				fr(&a, &b, &c);
			}
		}
	}

	clock_gettime(CLOCK_MONOTONIC, &nanos);
	end = getTimeInNanos(nanos);
	duration = end - start;
	printf("a is %lld; b is %lld. It took %ld.%ld'%ld s \n", a, b, getSeconds(duration), getMilli(duration), getMicro(duration));
}
