//
// Created by xhy on 2020/12/2.
//

#include <cstdarg>
#include "DirtyLogger.h"
#include <ctime>

FILE *logger = nullptr;

LOG_LEVEL log_level = LOG_LEVEL::LOG_INFO;

void initLogger(const std::string &logFileName, bool useStdout) {
    //? this is not a waring
    if (useStdout) {
        logger = stdout;
    } else {
        logger = fopen(logFileName.c_str(), "a+");
        if (!logger)logger = stderr;
    }
}

void setLogLevel(LOG_LEVEL level) {
    log_level = level;
}

void logInfo(LOG_LEVEL logLevel, const char *functionName, const char *fmt, ...) {
    if (logLevel < log_level) return;
    va_list args;
            va_start(args, fmt);
    time_t rawTime;
    time(&rawTime);
    struct tm *t = localtime(&rawTime);
    fprintf(logger, "[%.4d-%.2d-%.2d %.2d:%.2d:%.2d ", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour,
            t->tm_min,
            t->tm_sec);
    switch (logLevel) {
        case LOG_LEVEL::LOG_ERROR:
            fprintf(logger, " ERROR] ");
            break;
        case LOG_LEVEL::LOG_DEBUG:
            fprintf(logger, " DEBUG] ");
            break;
        case LOG_LEVEL::LOG_INFO:
            fprintf(logger, "  INFO] ");
            break;
        case LOG_LEVEL::LOG_WARNING:
            fprintf(logger, "  WARN] ");
            break;
        case LOG_LEVEL::NO_LOG:
            break;
    }
    fprintf(logger, "(%s) ", functionName);
    vfprintf(logger, fmt, args);
    fprintf(logger, "\n");
}

