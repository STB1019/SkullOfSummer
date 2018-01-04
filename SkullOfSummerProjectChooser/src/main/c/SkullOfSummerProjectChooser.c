/**
 * @file
 *
 * @author koldar
 * @date Jan 4, 2018
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "project_reader.h"

#define PROJECT_FILE "projects.dat"

static char readCharFromUser();

int main(int argc, const char* const args[]) {
	struct project_file* projects = parseProjectFile(PROJECT_FILE);
	char userInput;
	unsigned long seed;

	//get the rand seed
	if (argc == 2) {
		seed = atoll(args[1]);
	} else {
		seed = 0;
	}
	srand(seed);

	printAllAvailableProjects(projects);

	while(true) {
		printf("What do you want to do?\n");
		printf("\t[0]: pick a project\n");
		printf("\t1: exit\n");

		fflush(stdin);
		userInput = readCharFromUser();

		switch (userInput) {
		case '\n':
		case '0': {
			if (!isThereUnassignedProjects(projects)) {
				fprintf(stderr, "Sorry, all the projects have been assigned!\n");
			} else {
				struct project* project = getRandomProjectInProjectFile(projects);
				printf("I have chosen: \"%s\"!\n", project->name);
			}
			break;
		}
		case '1': {
			goto exit;
			break;
		}
		default: {
			fprintf(stderr, "Couldn't understand the input \"%c\"! Ignoring it.\n", userInput);
			break;
		}
		}
	}

	exit:
	printf("Thanks for having used this useless program!\n");
	destroyProjectFile(projects);
	return 0;
}

static char readCharFromUser() {
	char buffer[2];
	char ch;
	fgets(buffer, 2, stdin);
	while (true) {
		ch = fgetc(stdin);
		if (ch == '\n' || ch == EOF) {
			break;
		}
	}
	return buffer[0];
}
