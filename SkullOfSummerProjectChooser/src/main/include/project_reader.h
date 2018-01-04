/**
 * @file
 *
 * @author koldar
 * @date Jan 4, 2018
 */

#ifndef PROJECT_READER_H_
#define PROJECT_READER_H_

#include "project.h"

struct project_file {
	const char* filename;
	int unassignedProjects;
	int projectsSize;
	struct project* projects[];
};

struct project_file* parseProjectFile(const char* const filename);

void destroyProjectFile(struct project_file* const pf);

struct project* getRandomProjectInProjectFile(struct project_file* const pf);

bool isThereUnassignedProjects(const struct project_file* const pf);

void printAllAvailableProjects(const struct project_file* const pf);

#endif /* PROJECT_READER_H_ */
