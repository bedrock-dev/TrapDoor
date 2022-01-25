//
// 一个简单的日志类
// ，仅仅是简单的信息按照格式写入文件中，没有任何性能和可靠性保证 Created by xhy
// on 2020/12/2.
//
#define _WINSOCKAPI_

#include "DirtyLogger.h"

#include <Windows.h>

#include <cstdarg>
#include <ctime>

namespace trapdoor {
    namespace {
        LOG_LEVEL globalLogLevel = LOG_LEVEL::LOG_INFO;
        FILE *logger = nullptr;
        bool devMode = false;

        void setConsoleColor(int k) {
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, k);
        }

        int getLevelColor(LOG_LEVEL level) {
            switch (level) {
                case LOG_LEVEL::LOG_DEBUG:
                    return 10;
                case LOG_LEVEL::LOG_INFO:
                    return 7;
                case LOG_LEVEL::LOG_WARNING:
                    return 6;
                case LOG_LEVEL::LOG_ERROR:
                    return 4;
                case LOG_LEVEL::NO_LOG:
                    return 0;
            }
            return 0;
        }

        const char *getLevelLabel(LOG_LEVEL level) {
            switch (level) {
                case LOG_LEVEL::LOG_DEBUG:
                    return "DEBUG";
                case LOG_LEVEL::LOG_INFO:
                    return " INFO";
                case LOG_LEVEL::LOG_WARNING:
                    return "WARN";
                case LOG_LEVEL::LOG_ERROR:
                    return "ERROR";
                case LOG_LEVEL::NO_LOG:
                    return "?";
            }
            return "";
        }
    }  // namespace

    //初始化日志，不然不能使用
    void initLogger(const std::string &logFileName) {
        logger = fopen(logFileName.c_str(), "a+");
        if (!logger) logger = stderr;
        // L_INFO("TRAPDOOR LOGGER INIT");
    }

    //向日志里面打印信息
    //如果是开发者模式就打印所有日志，无视日志等级
    void logInfo(LOG_LEVEL level, const char *functionName, const char *fmt,
                 ...) {
        if (globalLogLevel > level && !devMode) return;
        setConsoleColor(getLevelColor(level));
        va_list args;
        va_start(args, fmt);
        time_t rawTime;
        time(&rawTime);
        struct tm *t = localtime(&rawTime);
        fprintf(logger, "[%.2d-%.2d %.2d:%.2d:%.2d]", t->tm_mon + 1, t->tm_mday,
                t->tm_hour, t->tm_min, t->tm_sec);
        fprintf(logger, "[%s]", getLevelLabel(globalLogLevel));
        fprintf(logger, "(%s) ", functionName);
        //输出到桌面(桌面输出不需要输出时间和函数名称)
        vfprintf(stdout, fmt, args);
        fprintf(stdout, "\n");
        fflush(stdout);
        //输出到日志文件
        vfprintf(logger, fmt, args);
        fprintf(logger, "\n");
        fflush(logger);
    }

    void setLogLevel(LOG_LEVEL log_level) { globalLogLevel = log_level; }

    void setDevMode(bool useDevMode) { devMode = useDevMode; }
    void newLogInfo(LOG_LEVEL level, const char *fileName,
                    const char *functionName, size_t line, const char *fmt,
                    ...) {
        if (globalLogLevel > level && !devMode) return;
    }
}  // namespace trapdoor
