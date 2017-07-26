#include "log.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdbool.h>
#include <libgen.h>
#include <stdlib.h>
#include <time.h>

const char* LOGLEVEL_TO_STRING[LOG_LEVEL_SIZE] = {
		"ALL",
		"DEBUG",
		"FINEST",
		"FINER",
		"FINE",
		"INFO",
		"WARNING",
		"ERROR",
		"CRITICAL",
		"NOLOG"
};

static char logBuffer[1000];

static void logToStdOut(int seconds, int milliseconds, const char* fileName, const char* functionName, const int lineNo, const LogLevel level, const char* message);
static void logToDevNull(int seconds, int milliseconds, const char* fileName, const char* functionName, const int lineNo, const LogLevel level, const char* message);

static void getCurrentTime(int* seconds, int* milliseconds);

static appenderFunction appenders = &logToStdOut;

void __generic_log_function(const LogLevel level, const char* absoluteFilePath, const char* functionName, const int lineNo, const char* format, ...) {
	char* fileName = basename(absoluteFilePath);
	va_list argList;
	va_start(argList, format);
	vsprintf(logBuffer, format, argList);
	va_end(argList);
	int s, ms;
	getCurrentTime(&s, &ms);
	appenders(s, ms, fileName, functionName, lineNo, level, logBuffer);
}

static void logToStdOut(int s, int ms, const char* fileName, const char* functionName, const int lineNo, const LogLevel level, const char* message) {
	printf("%03d:%03d %s:%s:%d[%s] %s\n", s, ms, fileName, functionName, lineNo, LOGLEVEL_TO_STRING[level], message);
	fflush(stdout);
}

static void logToDevNull(int s, int ms, const char* fileName, const char* functionName, const int lineNo, const LogLevel level, const char* message) {
}

static void getCurrentTime(int* seconds, int* milliseconds) {
	static bool first = true;
	static struct timespec origin;
	if (first) {
		clock_gettime(CLOCK_MONOTONIC, &origin);
		first = false;
	}
	
	struct timespec now;
	clock_gettime(CLOCK_MONOTONIC, &now);

	*seconds = (int)(now.tv_sec - origin.tv_sec);
	*milliseconds = (int)((now.tv_nsec - origin.tv_nsec) / 1000000);
}
