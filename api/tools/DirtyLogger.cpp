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
                case LOG_LEVEL::LOG_TRACE:
                    return 7;
                case LOG_LEVEL::LOG_DEBUG:
                    return 10;
                case LOG_LEVEL::LOG_INFO:
                    return 15;
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
                case LOG_LEVEL::LOG_TRACE:
                    return "TRAPDOOR TRACE";
                case LOG_LEVEL::LOG_DEBUG:
                    return "TRAPDOOR DEBUG";
                case LOG_LEVEL::LOG_INFO:
                    return "TRAPDOOR INFO";
                case LOG_LEVEL::LOG_WARNING:
                    return "TRAPDOOR WARN";
                case LOG_LEVEL::LOG_ERROR:
                    return "TRAPDOOR ERROR";
                case LOG_LEVEL::NO_LOG:
                    return "?";
            }
            return "";
        }

        void fprintNow(FILE *fp) {
            time_t rawTime;
            time(&rawTime);
            struct tm *t = localtime(&rawTime);
            fprintf(fp, "%.2d-%.2d %.2d:%.2d:%.2d", t->tm_mon + 1, t->tm_mday,
                    t->tm_hour, t->tm_min, t->tm_sec);
        }
    }  // namespace

    //初始化日志，不然不能使用
    void initLogger(const std::string &logFileName) {
        logger = fopen(logFileName.c_str(), "a+");
        if (!logger) logger = stderr;
        // L_INFO("TRAPDOOR LOGGER INIT");
    }

    /**
     * @brief 往之日文件中写入信息
     *  不论是否为开发模式，日志中全部写入除 trace的所有信息，日志基本格式如下
     *[date time][TR logleve](function) msg
     */
    // void logToFile(LOG_LEVEL level, const char *function, const char *fmt,

    //                ...) {
    //     if (level == LOG_LEVEL::LOG_TRACE) return;
    //     fprintNow(logger);
    //     fprintf(logger, "[%s](%s)", getLevelLabel(level), function);
    //     va_list args;
    //     va_start(args, fmt);
    //     vfprintf(logger, fmt, args);
    //     va_end(args);
    //     fprintf(logger, "\n");
    //     fflush(logger);
    // }
    /**
     * @brief 向输出流中打印调试信息
     * 如果是开发者模式  打印所有等级的信息
     *  如果是用户模式 打印等级大于等于globallevel的信息
     */

    // void logToStdout(LOG_LEVEL level, const char *fmt, ...) {
    //     if (globalLogLevel > level && !devMode) return;
    //     setConsoleColor(getLevelColor(level));
    //     va_list args;
    //     va_start(args, fmt);
    //     vfprintf(stdout, fmt, args);
    //     va_end(args);
    //     printf("\n");
    //     fflush(stdout);
    //     setConsoleColor(getLevelColor(LOG_LEVEL::LOG_INFO));
    // }

    void logInfo(LOG_LEVEL level, const char *functionName, const char *fmt,
                 ...) {
        if (level != LOG_LEVEL::LOG_TRACE) {
            /*
             *  往日志文件中写入信息
             *  不论是否为开发模式，日志中全部写入除
             * trace的所有信息，日志基本格式如下 [date time][TR
             * logleve](function) msg
             */
            fprintf(logger, "[");
            fprintNow(logger);
            fprintf(logger, "%s](%s) ", getLevelLabel(level), functionName);
            va_list args;
            va_start(args, fmt);
            vfprintf(logger, fmt, args);
            va_end(args);
            fprintf(logger, "\n");
            fflush(logger);
        }

        if (globalLogLevel > level && !devMode) return;
        setConsoleColor(getLevelColor(level));
        fprintf(stdout, "[");
        fprintNow(stdout);
        printf(" %s] ", getLevelLabel(level));
        va_list args;
        va_start(args, fmt);
        vfprintf(stdout, fmt, args);
        va_end(args);
        printf("\n");
        fflush(stdout);
        setConsoleColor(getLevelColor(LOG_LEVEL::LOG_INFO));
    }

    void setLogLevel(LOG_LEVEL log_level) { globalLogLevel = log_level; }

    void setDevMode(bool useDevMode) {
        devMode = useDevMode;
        L_INFO(" +===========================+");
        L_TRACE("|  This is a trace message  |");
        L_DEBUG("|  This is a debug message  |");
        L_INFO(" |  This is a info message   |");
        L_WARNING(" |  This is a warning mssage |");
        L_ERROR("|  This is a error message  |");
        L_INFO(" +===========================+\n");
    }
    void newLogInfo(LOG_LEVEL level, const char *fileName,
                    const char *functionName, size_t line, const char *fmt,
                    ...) {
        if (globalLogLevel > level && !devMode) return;
    }
}  // namespace trapdoor
