//
// 一个简单的日志类 ，仅仅是简单的信息按照格式写入文件中，没有任何性能和可靠性保证
// Created by xhy on 2020/12/2.
//

#include <cstdarg>
#include <ctime>
#include "Windows.h"
#include "DirtyLogger.h"

namespace trapdoor {

    namespace {
        LOG_LEVEL logLevel = LOG_LEVEL::LOG_DEBUG;

        FILE *logger = nullptr;
        bool loggerPrintTime = true;
        bool loggerPrintFunctionName = true;
    }

//初始化日志，不然不能使用



    void
    initLogger(const std::string &logFileName, bool useStdout, bool printTime, bool printFunctionName) {
        loggerPrintFunctionName = printFunctionName;
        loggerPrintTime = printTime;
        //? this is not a waring
        if (useStdout) {
            logger = stdout;
        } else {
            logger = fopen(logFileName.c_str(), "a+");
            L_INFO("\n-------------------------TRAPDOOR LOG FILE---------------------------\n "
                   "-----------------------------init BDS------------------------------- \n");
            if (!logger)logger = stderr;
        }
    }

//向日志里面打印信息

    void logInfo(LOG_LEVEL level, const char *functionName, const char *fmt, ...) {
        if (logLevel > level) return;
        va_list args;
                va_start(args, fmt);
        time_t rawTime;
        time(&rawTime);
        struct tm *t = localtime(&rawTime);
        if (loggerPrintTime) {
            fprintf(logger, "[%.2d-%.2d %.2d:%.2d:%.2d ", t->tm_mon + 1, t->tm_mday, t->tm_hour,
                    t->tm_min,
                    t->tm_sec);
        }

        switch (logLevel) {
            case LOG_LEVEL::LOG_ERROR:
                fprintf(logger, "ERROR] ");
                break;
            case LOG_LEVEL::LOG_DEBUG:
                fprintf(logger, "DEBUG] ");
                break;
            case LOG_LEVEL::LOG_INFO:
                fprintf(logger, "INFO] ");
                break;
            case LOG_LEVEL::LOG_WARNING:
                fprintf(logger, "WARN] ");
                break;
            case LOG_LEVEL::NO_LOG:
                break;
        }
//
//        size_t functionLength = strlen(functionName);
//        if (functionLength >= 20) {
//            functionName += 17;
//        }
        if (loggerPrintFunctionName) {
            fprintf(logger, "(%s) ", functionName);
        }
        vfprintf(logger, fmt, args);
        fprintf(logger, "\n");
        fflush(logger);
    }

    void setLogLevel(LOG_LEVEL log_level) {
        logLevel = log_level;
    }
}

