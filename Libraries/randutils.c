#include "randutils.h"

#include <stdlib.h>

int randRange(int min, int max, bool lb, bool ub) {
	min += lb ? 0 : 1;
	max += ub ? 1 : 0;
	return (rand() % (max - min)) + min;
}
