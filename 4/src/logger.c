#include "logger.h"

LogLevel GLOBAL_LOG_LEVEL = LOG_INFO;
FILE* log_file = NULL;

static const char* level_strings[] = {
    "DEBUG",
    "INFO",
    "WARNING",
    "ERROR"
};

void log_init(const char* filename, LogLevel level) {
    GLOBAL_LOG_LEVEL = level;
    if (filename) {
        log_file = fopen(filename, "a");
    }
}

void log_close(void) {
    if (log_file) {
        fclose(log_file);
        log_file = NULL;
    }
}

static void log_message(LogLevel level, const char* format, va_list args) {
    if (level < GLOBAL_LOG_LEVEL) return;

    time_t now;
    time(&now);
    char timestamp[26];
    ctime_r(&now, timestamp);
    timestamp[24] = '\0'; // Remove newline

    FILE* output = log_file ? log_file : stdout;
    
    fprintf(output, "[%s] %s: ", timestamp, level_strings[level]);
    vfprintf(output, format, args);
    fprintf(output, "\n");
    fflush(output);
}

void log_debug(const char* format, ...) {
    va_list args;
    va_start(args, format);
    log_message(LOG_DEBUG, format, args);
    va_end(args);
}

void log_info(const char* format, ...) {
    va_list args;
    va_start(args, format);
    log_message(LOG_INFO, format, args);
    va_end(args);
}

void log_warning(const char* format, ...) {
    va_list args;
    va_start(args, format);
    log_message(LOG_WARNING, format, args);
    va_end(args);
}

void log_error(const char* format, ...) {
    va_list args;
    va_start(args, format);
    log_message(LOG_ERROR, format, args);
    va_end(args);
}
