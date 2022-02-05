//
// Created by xhy on 2020/12/2.
//

#ifndef TRAPDOOR_DIRTYLOGGER_H
#define TRAPDOOR_DIRTYLOGGER_H

#include <cstdio>
#include <string>
#ifdef WIN32
#define __FILENAME__                                                           \
    (__builtin_strrchr(__FILE__, '\\') ? __builtin_strrchr(__FILE__, '\\') + 1 \
                                       : __FILE__)
#else
#define __FILENAME__                                                         \
    (__builtin_strrchr(__FILE__, '/') ? __builtin_strrchr(__FILE__, '/') + 1 \
                                      : __FILE__)
#endif

#define L_DEBUG(fmt, ...)                                                \
    trapdoor::logInfo(trapdoor::LOG_LEVEL::LOG_DEBUG, __FUNCTION__, fmt, \
                      __VA_ARGS__)
#define L_INFO(fmt, ...)                                                \
    trapdoor::logInfo(trapdoor::LOG_LEVEL::LOG_INFO, __FUNCTION__, fmt, \
                      __VA_ARGS__)
#define L_WARNING(fmt, ...)                                                \
    trapdoor::logInfo(trapdoor::LOG_LEVEL::LOG_WARNING, __FUNCTION__, fmt, \
                      __VA_ARGS__)
#define L_ERROR(fmt, ...)                                                \
    trapdoor::logInfo(trapdoor::LOG_LEVEL::LOG_ERROR, __FUNCTION__, fmt, \
                      __VA_ARGS__)
namespace trapdoor {
    enum class LOG_LEVEL {
        LOG_DEBUG = 0,
        LOG_INFO = 1,
        LOG_WARNING = 2,
        LOG_ERROR = 3,
        NO_LOG = 4
    };

    void initLogger(const std::string &logFileName);

    void setLogLevel(LOG_LEVEL level);

    void logInfo(LOG_LEVEL logLevel, const char *functionName, const char *fmt,
                 ...);

    void newLogInfo(LOG_LEVEL logLevel, const char *fileName,
                    const char *functionName, size_t line, const char *fmt,
                    ...);

    void setDevMode(bool useDevMode);

}  // namespace trapdoor
#endif  // TRAPDOOR_DIRTYLOGGER_H
