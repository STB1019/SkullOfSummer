#include <stdio.h>
#include <string.h>
#include "utils.h"
#include "csv.h"
#include "json.h"
#include "conversion.h"

void printHeader() {
	//Formatting skillz level 9001
	printf("      SkullOfSummer 2017 - Lorenzo Nodari - SbIEEE@UniBs\n");
	printf("                      -- DISCLAIMER --\n");
	printf("   This program is to be considered just a proof-of-concept\n");
	printf("This executable in only used to show that the library \"works\"\n");
}

void printHelpAndQuitConverter() {
	printf("Usage: ezparse <filename> <outputname>\n");
	exit(0);
}

void printHelpAndQuitPrinter() {
	printf("Usage: ezparse <filename>\n");
	exit(0);
}

#ifdef CONVERTER_BUILD

#ifdef PRINTER_BUILD
#undef PRINTER_BUILD
#endif

int main(int argc, char * argv[]) {
	if (argc != 3) {
		printHelpAndQuitConverter();
	}

	printHeader();
	FILE * file = fopen(argv[1], "r");

	if (file == NULL) {
		printf("Input file not found\n");
		exit(1);
	}

	sos_list_t * file_scheme = parseCSV(file);
	printf("File scheme:\n\n");
	sos_printList(file_scheme);
	if (convertToJSON(file_scheme, argv[2])) {
		printf("Converted!\n");
		return 0;
	}
	else {
		printf("Conversion unsuccesful.\n");
		return 1;
	}
}
#endif

#ifdef PRINTER_BUILD

#define CSV 1
#define JSON 2

/**
 * Determina il tipo di file dall'estensione (lo fa il gcc quindi lo posso fare pure io)
 */
int determineFileType(char * file_name) {
	int read_char;

	do {
		read_char = *(file_name++);
	} while (read_char != '.');

	if (strncmp(file_name, "csv", 3) == 0) {
		return CSV;
	}
	else if (strncmp(file_name, "json", 4) == 0) {
		return JSON;
	}
	else {
		return -1;
	}
}

int main(int argc, char * argv[]) {
	sos_list_t * file_scheme;
	FILE * file;

	if (argc != 2) {
		printHelpAndQuitPrinter();
	}

	printHeader();
	file = fopen(argv[1], "r");

	if (file == NULL) {
		printf("Input file not found\n");
		exit(1);
	}

	switch (determineFileType(argv[1])) {

	case CSV:
		file_scheme = parseCSV(file);
		break;

	case JSON:
		file_scheme = parseJSON(file);
		break;

	default:
		printf("Unknown file type\n");
		exit(1);
	}

	if (file_scheme == NULL) {
		printf("Could not parse input file\n");
		exit(1);
	}

	printf("\t### FILE SCHEME ###\n");
	sos_printList(file_scheme);
	freeList(file_scheme);
	fclose(file);
	return 0;
}
#endif
