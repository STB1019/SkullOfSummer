#include "professor.h"
#include "utils.h"
#include <stdlib.h>

static void computeNextVote(professor* p);

void setupProfessor(professor* p) {
	p->votesChosen = 0;
	p->meanVotes = 0.;
	computeNextVote(p);
}

void evaluateStudent(student* s, professor* p) {
	if (p->nextVote >= 18) {
		addExamOutcome(s, p->nextVote);
	}
	computeOnlineMean(&p->meanVotes, &p->votesChosen, p->nextVote);
	computeNextVote(p);
}

static void computeNextVote(professor* p) {
	p->nextVote = 14 + (rand() % 17);
}
