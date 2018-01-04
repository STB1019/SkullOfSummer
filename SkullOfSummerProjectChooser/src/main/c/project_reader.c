/**
 * @file
 *
 * @author koldar
 * @date Jan 4, 2018
 */

#include "project_reader.h"
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#define MAX_SIZE 100

static bool isLineAComment(const char* const line);
static const char* getPtrInLineForProject(const char* const line);
static int getProjectsNumber(const char* const filename);
static int getRandom(int min, int max, bool minIncluded, bool maxIncluded);

struct project_file* parseProjectFile(const char* const filename) {
	int projectNumber = getProjectsNumber(filename);

	struct project_file* retval = malloc(sizeof(struct project_file) + projectNumber * sizeof(struct project));
	if (retval == NULL) {
		exit(1);
	}

	retval->filename = filename;
	retval->projectsSize = projectNumber;
	retval->unassignedProjects = projectNumber;

	FILE* fin = fopen(filename, "r");
	if (fin == NULL) {
		exit(2);
	}

	char line[MAX_SIZE];
	char projectNameBuffer[MAX_SIZE];
	int nextProject = 0;

	while(fgets(line, MAX_SIZE, fin) != NULL) {
		if (isLineAComment(line)) {
			//the line is a comment. Ignore
			continue;
		}
		const char* projectName = getPtrInLineForProject(line);
		if (projectName == NULL) {
			//the line does not represent a project name. Ignore
			continue;
		}
		snprintf(projectNameBuffer, MAX_SIZE, "%s", projectName);
		projectNameBuffer[strlen(projectNameBuffer)-1] = '\0'; //removing trailing newline
		//we create a project
		retval->projects[nextProject] = initProject(strdup(projectNameBuffer));
		nextProject++;
	}

	return retval;
}

void destroyProjectFile(struct project_file* const pf) {
	for (int i=0; i<pf->projectsSize; i++) {
		destroyProject(pf->projects[i]);
	}
	free(pf);
}

struct project* getRandomProjectInProjectFile(struct project_file* const pf) {
	int index;
	do {
		index = getRandom(0, pf->projectsSize, true, true);
	} while (pf->projects[index]->alreadyAssigned);
	pf->projects[index]->alreadyAssigned = true;
	pf->unassignedProjects -= 1;
	return pf->projects[index];
}

bool isThereUnassignedProjects(const struct project_file* const pf) {
	return pf->unassignedProjects > 0;
}

void printAllAvailableProjects(const struct project_file* const pf) {
	printf("Available project are %d\n", pf->projectsSize);
	for (int i=0; i<pf->projectsSize; i++) {
		printf("%3d) %s\n", i, pf->projects[i]->name);
	}
}

static int getRandom(int min, int max, bool minIncluded, bool maxIncluded) {
	min += minIncluded ? 0 : 1;
	max -= maxIncluded ? 0 : 1;

	//both min and max are included
	return min + (rand() % (max - min));
}

static int getProjectsNumber(const char* const filename) {
	FILE* fin = fopen(filename, "r");
	if (fin == NULL) {
		exit(2);
	}

	char line[MAX_SIZE];
	int retval = 0;
	while(fgets(line, MAX_SIZE, fin) != NULL) {
		if (isLineAComment(line)) {
			//the line is a comment. Ignore
			continue;
		}
		const char* projectName = getPtrInLineForProject(line);
		if (projectName == NULL) {
			//the line does not represent a project name. Ignore
			continue;
		}

		retval++;
	}

	return retval;
}

static bool isLineAComment(const char* const line) {
	return line[0] == '#';
}

static const char* getPtrInLineForProject(const char* const line) {
	int i=0;
	bool retval = false;
	while (line[i] != '\0') {
		if (line[i]==' ' || line[i]=='\t' || line[i]=='\n') {
			i++;
		}else {
			return &line[i];
		}
	}
	return NULL;
}
