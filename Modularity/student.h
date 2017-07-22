#ifndef STUDENT_H__
#define STUDENT_H__

#include <stdbool.h>

struct professor;

typedef struct {
	int id;
	char* name;
	char* surname;
	int examsDone;
	float mean;
	struct professor* supervisor;
} student;

void addExamOutcome(student* s, float outcome);

char* getFullName(const student* s, char* buffer);

bool tryToCorruptSupervisor(const student* s);

#endif
