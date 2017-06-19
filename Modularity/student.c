
#include <stdio.h>
#include "student.h"
#include "utils.h"
#include "professor.h"

void addExamOutcome(student* s, float outcome) {
	computeOnlineMean(&s->mean, &s->examsDone, outcome);
	s->examsDone++;
}

char* getFullName(const student* s, char* buffer) {
	sprintf(buffer, "%s %s", s->name, s->surname);
	return buffer;
}

bool tryToCorruptSupervisor(const student* s) {
	professor* p = s->supervisor;
	if (getProbability(p->corruptability) == 1) {
		p->nextVote = 30;
	}	
}

