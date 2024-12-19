// logger.h
#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>
#include <time.h>
#include <stdarg.h>

// Log levels
typedef enum {
    LOG_DEBUG,
    LOG_INFO,
    LOG_WARNING,
    LOG_ERROR
} LogLevel;

// Global log level setting
extern LogLevel GLOBAL_LOG_LEVEL;
extern FILE* log_file;

// Initialize logger
void log_init(const char* filename, LogLevel level);

// Close logger
void log_close(void);

// Logging functions
void log_debug(const char* format, ...);
void log_info(const char* format, ...);
void log_warning(const char* format, ...);
void log_error(const char* format, ...);

#endif // LOGGER_H

