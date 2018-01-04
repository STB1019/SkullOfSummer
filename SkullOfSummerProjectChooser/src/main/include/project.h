/**
 * @file
 *
 * @author koldar
 * @date Jan 4, 2018
 */

#ifndef PROJECT_H_
#define PROJECT_H_

#include <stdbool.h>

struct project {
	const char* name;
	bool alreadyAssigned;
};

struct project* initProject(const char* const name);

void destroyProject(struct project* const p);

#endif /* PROJECT_H_ */
