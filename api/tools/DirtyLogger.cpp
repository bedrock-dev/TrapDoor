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
        LOG_LEVEL logLevel = LOG_LEVEL::LOG_INFO;
        FILE *logger = nullptr;
        bool devMode = false;

        void setColor(int k) {
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, k);
        }
    }

//初始化日志，不然不能使用
    void initLogger(const std::string &logFileName) {
        logger = fopen(logFileName.c_str(), "a+");
        L_INFO("\n-------------------------TRAPDOOR LOG FILE---------------------------\n "
               "-----------------------------init BDS------------------------------- \n");
        if (!logger)logger = stderr;
    }


//向日志里面打印信息
//如果是开发者模式就打印所有日志，无视日志等级
    void logInfo(LOG_LEVEL level, const char *functionName, const char *fmt, ...) {
        if (logLevel > level && !devMode) return;
        switch (level) {
            case LOG_LEVEL::LOG_DEBUG:
                setColor(10); //green
                break;
            case LOG_LEVEL::LOG_INFO:
                setColor(7); //white
                break;
            case LOG_LEVEL::LOG_WARNING:
                setColor(6);
                break;
            case LOG_LEVEL::LOG_ERROR:
                setColor(4);
                break;
            case LOG_LEVEL::NO_LOG:
                break;
        }
        va_list args;
                va_start(args, fmt);
        time_t rawTime;
        time(&rawTime);
        struct tm *t = localtime(&rawTime);
        fprintf(logger, "[%.2d-%.2d %.2d:%.2d:%.2d]", t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);
        switch (logLevel) {
            case LOG_LEVEL::LOG_ERROR:
                fprintf(logger, "[ERROR] ");
                break;
            case LOG_LEVEL::LOG_DEBUG:
                fprintf(logger, "[DEBUG] ");
                break;
            case LOG_LEVEL::LOG_INFO:
                fprintf(logger, "[INFO] ");
                break;
            case LOG_LEVEL::LOG_WARNING:
                fprintf(logger, "[WARN] ");
                break;
            case LOG_LEVEL::NO_LOG:
                break;
        }

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

    void setLogLevel(LOG_LEVEL log_level) {
        logLevel = log_level;
    }

    void setDevMode(bool useDevMode) {
        devMode = useDevMode;
    }
}

