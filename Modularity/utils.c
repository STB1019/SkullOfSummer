
#include <stdlib.h>
#include "utils.h"

void computeOnlineMean(float* mean, int* n, float newValue) {
	float oldMean = *mean;
	float newMean = oldMean + (newValue - oldMean)/(*n + 1);
	*mean = newMean;
	*n = *n + 1;
}

bool getProbability(float prob) {
	if ((rand() % 1000) < (int)(prob * 1000)) {
		return 1;
	}
	return 0;
}
