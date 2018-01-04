/**
 * @file
 *
 * @author koldar
 * @date Jan 4, 2018
 */

#include <stdlib.h>
#include "project.h"

struct project* initProject(const char* const name) {
	struct project* retval = malloc(sizeof(struct project));
	if (retval == NULL) {
		exit(1);
	}
	retval->name = name;
	retval->alreadyAssigned = false;

	return retval;
}

void destroyProject(struct project* const p) {
	free((void*)p->name);
	free(p);
}
