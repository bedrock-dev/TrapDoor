#define _WINSOCKAPI_
// clang-format off
#include <Windows.h>
#include <Psapi.h>
// clang-format on
#include "process_stat.h"

#include <cassert>
#include <cstdio>
#include <iostream>

/// 时间转换
static uint64_t file_time_2_utc(FILETIME *ftime) {
    LARGE_INTEGER li;
    assert(ftime);
    li.LowPart = ftime->dwLowDateTime;
    li.HighPart = ftime->dwHighDateTime;
    return li.QuadPart;
}

/// 获得CPU的核数
static int get_processor_number() {
    SYSTEM_INFO info;
    GetSystemInfo(&info);
    return (int)info.dwNumberOfProcessors;
}

int get_cpu_usage() {
    // cpu数量
    static int processor_count_ = -1;
    //上一次的时间
    static int64_t last_time_ = 0;
    static int64_t last_system_time_ = 0;
    FILETIME now;
    FILETIME creation_time;
    FILETIME exit_time;
    FILETIME kernel_time;
    FILETIME user_time;
    int64_t system_time;
    int64_t time;
    int64_t system_time_delta;
    int64_t time_delta;
    int cpu = -1;
    if (processor_count_ == -1) {
        processor_count_ = get_processor_number();
    }

    GetSystemTimeAsFileTime(&now);
    //获取想换时间
    if (!GetProcessTimes(GetCurrentProcess(), &creation_time, &exit_time,
                         &kernel_time, &user_time)) {
        printf("error GetProcessTimes\n");
        return -1;
    }

    system_time =
        (file_time_2_utc(&kernel_time) + file_time_2_utc(&user_time)) /
        processor_count_;
    time = file_time_2_utc(&now);

    if ((last_system_time_ == 0) || (last_time_ == 0)) {
        //第一此返回-1
        last_system_time_ = system_time;
        last_time_ = time;
        return -1;
    }

    system_time_delta = system_time - last_system_time_;
    time_delta = time - last_time_;
    assert(time_delta != 0);

    if (time_delta == 0) {
        return -1;
    }

    // We add time_delta / 2 so the result is rounded.
    cpu = (int)((system_time_delta * 100 + time_delta / 2) / time_delta);
    last_system_time_ = system_time;
    last_time_ = time;
    return cpu;
}

static float CalculateCPULoad(unsigned long long idleTicks,
                              unsigned long long totalTicks) {
    static unsigned long long _previousTotalTicks = 0;
    static unsigned long long _previousIdleTicks = 0;

    unsigned long long totalTicksSinceLastTime =
        totalTicks - _previousTotalTicks;
    unsigned long long idleTicksSinceLastTime = idleTicks - _previousIdleTicks;

    float ret =
        1.0f - ((totalTicksSinceLastTime > 0)
                    ? ((float)idleTicksSinceLastTime) / totalTicksSinceLastTime
                    : 0);

    _previousTotalTicks = totalTicks;
    _previousIdleTicks = idleTicks;
    return ret;
}

// Returns 1.0f for "CPU fully pinned", 0.0f for "CPU idle", or somewhere in
// between You'll need to call this at regular intervals, since it measures the
// load between the previous call and the current one.  Returns -1.0 on error.
float GetCPULoad() {
    FILETIME idleTime, kernelTime, userTime;
    return GetSystemTimes(&idleTime, &kernelTime, &userTime)
               ? CalculateCPULoad(
                     file_time_2_utc(&idleTime),
                     file_time_2_utc(&kernelTime) + file_time_2_utc(&userTime))
               : -1.0f;
}

int get_memory_usage(uint64_t *mem, uint64_t *vmem) {
    PROCESS_MEMORY_COUNTERS pmc;
    if (GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc))) {
        if (mem) *mem = pmc.WorkingSetSize;
        if (vmem) *vmem = pmc.PagefileUsage;
        return 0;
    }
    return -1;
}

int getSystemMemorySize(uint64_t *total, uint64_t *free) {
    MEMORYSTATUSEX statex;
    statex.dwLength = sizeof(statex);
    GlobalMemoryStatusEx(&statex);
    if (total) *total = statex.ullTotalPhys;
    if (free) *free = statex.ullAvailPhys;
    return 0;
}

int get_io_bytes(uint64_t *read_bytes, uint64_t *write_bytes) {
    IO_COUNTERS io_counter;
    if (GetProcessIoCounters(GetCurrentProcess(), &io_counter)) {
        if (read_bytes) *read_bytes = io_counter.ReadTransferCount;
        if (write_bytes) *write_bytes = io_counter.WriteTransferCount;
        return 0;
    }
    return -1;
}