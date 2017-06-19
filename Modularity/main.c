
#include "student.h"
#include "professor.h"
#include <stdio.h>

int main(const int argc, const char* args) {

	professor mario = {"Mario", "Rossi", 0, 0.0, 0, 0.5};
	professor carlo = {"Carlo", "RosaConfetto", 0, 0.0, 0, 0.9};
	professor antonio = {"Antonio", "Verdi", 0, 0.0, 0, 0.1};

	setupProfessor(&mario);
	setupProfessor(&carlo);
	setupProfessor(&antonio);

	student lorenzo = {76953, "Lorenzo", "Giallo", 0, 0.0, &mario};
	student luca = {76953, "Luca", "Neri", 0, 0.0, &antonio};
	student maria = {76953, "Maria", "Arancione", 0, 0.0, &mario};

	evaluateStudent(&lorenzo, &mario);
	evaluateStudent(&luca, &carlo);
	evaluateStudent(&luca, &mario);
	evaluateStudent(&maria, &antonio);
	evaluateStudent(&lorenzo, &carlo);
	evaluateStudent(&luca, &antonio);
	evaluateStudent(&maria, &mario);

	char buffer[300];
	printf("%s: %2.5f\n", getFullName(&lorenzo, buffer), lorenzo.mean);
	printf("%s: %2.5f\n", getFullName(&luca, buffer), luca.mean);
	printf("%s: %2.5f\n", getFullName(&maria, buffer), maria.mean);
}
