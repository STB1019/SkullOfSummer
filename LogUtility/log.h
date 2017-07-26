#ifndef LOG_H_
#define LOG_H_

#ifdef QUICK_LOG
#endif

#define __LOG_ALL		0
#define __LOG_DEBUG		1
#define __LOG_FINEST		2
#define __LOG_FINER		3
#define __LOG_FINE		4
#define __LOG_INFO		5
#define __LOG_WARNING		6
#define __LOG_ERROR		7
#define __LOG_CRITICAL		8
#define __LOG_OFF 		9

typedef enum LogLevel {
	LOG_ALL = __LOG_ALL,
	LOG_DEBUG = __LOG_DEBUG,
	LOG_FINEST = __LOG_FINEST,
	LOG_FINER = __LOG_FINER,
	LOG_FINE = __LOG_FINE,
	LOG_INFO = __LOG_INFO,
	LOG_WARNING = __LOG_WARNING,
	LOG_ERROR = __LOG_ERROR,
	LOG_CRITICAL = __LOG_CRITICAL,
	LOG_OFF = __LOG_OFF
} LogLevel;

#define  LOG_LEVEL_SIZE 10

typedef void (*appenderFunction)(int s, int ms, const char* file, const char* function, const int lineno, const LogLevel level, const char* message);

void __generic_log_function(const LogLevel level, const char* fileName, const char* functionName, const int lineNo, const char* format, ...);


#ifndef LOG_BUFFER
#	define LOG_BUFFER __cutils_log_buffer
#endif
#define log_buffer LOG_BUFFER

#ifndef LOG_BUFFER_SIZE
#	define LOG_BUFFER_SIZE 300
#endif


#if QUICK_LOG > __LOG_DEBUG
#	pragma message "DEBUG LOG TURNED OFF"
#	define debug(format,...) 0
#else
#	define debug(format,...) __generic_log_function(LOG_DEBUG, __FILE__, __FUNCTION__, __LINE__, format, ##__VA_ARGS__)
#endif

#if QUICK_LOG > __LOG_FINEST
#	pragma message "FINEST LOG TURNED OFF"
#	define finest(format,...) 0
#else
#	define finest(format,...) __generic_log_function(LOG_FINEST, __FILE__, __FUNCTION__, __LINE__, format, ##__VA_ARGS__)
#endif

#if QUICK_LOG > __LOG_FINER
#	pragma message "FINER LOG TURNED OFF"
#	define finer(format,...) 0
#else
#	define finer(format,...) __generic_log_function(LOG_FINER, __FILE__, __FUNCTION__, __LINE__, format, ##__VA_ARGS__)
#endif

#if QUICK_LOG > __LOG_FINE
#	pragma message "FINER LOG TURNED OFF"
#	define fine(format,...) 0
#else
#	define fine(format,...) __generic_log_function(LOG_FINE, __FILE__, __FUNCTION__, __LINE__, format, ##__VA_ARGS__)
#endif

#if QUICK_LOG > __LOG_INFO
#	pragma message "INFO LOG TURNED OFF"
#	define info(format,...) 0
#else
#	define info(format,...) __generic_log_function(LOG_INFO, __FILE__, __FUNCTION__, __LINE__, format, ##__VA_ARGS__)
#endif

#if QUICK_LOG > __LOG_WARNING
#	pragma message "WARNING LOG TURNED OFF"
#	define warning(format,...) 0
#else
#	define warning(format,...) __generic_log_function(LOG_WARNING, __FILE__, __FUNCTION__, __LINE__, format, ##__VA_ARGS__)
#endif

#if QUICK_LOG > __LOG_ERROR
#	pragma message "ERROR LOG TURNED OFF"
#	define error(format,...) 0
#else
#	define error(format,...) __generic_log_function(LOG_ERROR, __FILE__, __FUNCTION__, __LINE__, format, ##__VA_ARGS__)
#endif

#if QUICK_LOG > __LOG_CRITICAL
#	pragma message "CRITICAL LOG TURNED OFF"
#	define critical(format,...) 0
#else
#	define critical(format,...) __generic_log_function(LOG_CRITICAL, __FILE__, __FUNCTION__, __LINE__, format, ##__VA_ARGS__)
#endif

#endif /* LOG_H_ */
