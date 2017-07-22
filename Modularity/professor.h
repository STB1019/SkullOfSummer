#ifndef PROFESSOR_H__
#define PROFESSOR_H__

#include "student.h"

typedef struct professor {
	char* name;
	char* surname;
	float nextVote;
	float meanVotes;
	int votesChosen;
	float corruptability;
} professor;

void setupProfessor(professor* p);

void evaluateStudent(student* s, professor* p);

#endif
