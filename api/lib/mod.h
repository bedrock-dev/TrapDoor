#pragma once
#define _WINSOCKAPI_

#include <iostream>

#include "Windows.h"
#include "detours.h"
#include "detver.h"

using VA = unsigned __int64;
using RVA = unsigned long int;

#include <cstdio>

#define _EXPORTED _declspec(dllexport)

inline const char *Hook_wrap(void **pOriginal, void *f) {
    int error = DetourTransactionBegin();
    if (error != NO_ERROR) {
        return "Hook: DetourTransactionBegin Error";
    }
    error = DetourUpdateThread(GetCurrentThread());
    if (error != NO_ERROR) {
        return "Hook: DetourUpdateThread Error";
    }
    error = DetourAttach(pOriginal, (void *)f);
    if (error != NO_ERROR) {
        return "Hook: DetourAttach Error";
    }
    error = DetourTransactionCommit();
    if (error != NO_ERROR) {
        return "Hook: DetourTransactionCommit Error";
    }
    return nullptr;
}

inline void Hook(void **pOriginal, void *f, const char *prefix) {
    auto ret = Hook_wrap(pOriginal, f);
    fprintf(stdout, "hook :%s\n", prefix);
    if (ret) {
        fprintf(stderr, "[!] Hook error at %s : %s\n", ret, prefix);
    }
}

inline VA GetVA(RVA off) { return (VA)GetModuleHandle(nullptr) + (VA)off; }

#define TD_CONCAT3_I(a, b, c) a##b##c
#define TD_CONCAT3(a, b, c) TD_CONCAT3_I(a, b, c)
#define THook(ret, iname, ...)                                          \
    struct TD_CONCAT3(TDHook_, __LINE__, iname) {                       \
        static ret (*original)(__VA_ARGS__);                            \
        _EXPORTED static ret p(__VA_ARGS__);                            \
        TD_CONCAT3(TDHook_, __LINE__, iname)() {                        \
            original = (decltype(original))GetVA(iname);                \
            Hook((void **)&original, (void *)&p, #iname);               \
        }                                                               \
    };                                                                  \
    static TD_CONCAT3(TDHook_, __LINE__, iname) tdh##iname;             \
    ret (*TD_CONCAT3(TDHook_, __LINE__, iname)::original)(__VA_ARGS__); \
    ret TD_CONCAT3(TDHook_, __LINE__, iname)::p(__VA_ARGS__)
#define FNTYPE_DEF(...) VA (*)(__VA_ARGS__)
#define FNTYPE_DEF_0 FNTYPE_DEF()
#define FNTYPE_DEF_1 FNTYPE_DEF(VA)
#define FNTYPE_DEF_2 FNTYPE_DEF(VA, VA)
#define FNTYPE_DEF_3 FNTYPE_DEF(VA, VA, VA)
#define FNTYPE_DEF_4 FNTYPE_DEF(VA, VA, VA, VA)
#define FNTYPE_DEF_5 FNTYPE_DEF(VA, VA, VA, VA, VA)
#define FNTYPE_DEF_6 FNTYPE_DEF(VA, VA, VA, VA, VA, VA)
#define FNTYPE_DEF_7 FNTYPE_DEF(VA, VA, VA, VA, VA, VA, VA)
#define FNTYPE_DEF_8 FNTYPE_DEF(VA, VA, VA, VA, VA, VA, VA, VA)
#define FNTYPE_DEF_9 FNTYPE_DEF(VA, VA, VA, VA, VA, VA, VA, VA, VA)
#define FNTYPE_DEF_10 FNTYPE_DEF(VA, VA, VA, VA, VA, VA, VA, VA, VA, VA)
#define FNTYPE_DEF_11 FNTYPE_DEF(VA, VA, VA, VA, VA, VA, VA, VA, VA, VA, VA)
#define FNTYPE_DEF_12 FNTYPE_DEF(VA, VA, VA, VA, VA, VA, VA, VA, VA, VA, VA, VA)
#define FNTYPE_DEF_13 \
    FNTYPE_DEF(VA, VA, VA, VA, VA, VA, VA, VA, VA, VA, VA, VA, VA)
#define FNTYPE_DEF_14 \
    FNTYPE_DEF(VA, VA, VA, VA, VA, VA, VA, VA, VA, VA, VA, VA, VA, VA)
#define FNTYPE_DEF_15 \
    FNTYPE_DEF(VA, VA, VA, VA, VA, VA, VA, VA, VA, VA, VA, VA, VA, VA, VA)

#define SYM_PTR(TYPE, SYM_RVA)                                           \
    reinterpret_cast<TYPE>(reinterpret_cast<VA>(GetModuleHandle(NULL)) + \
                           SYM_RVA)
#define SYM_CALL(TYPE, SYM_RVA, ...) SYM_PTR(TYPE, SYM_RVA)(__VA_ARGS__)
#define SYM_CALL_0(SYM_RVA, ...) SYM_CALL(FNTYPE_DEF_0, SYM_RVA, __VA_ARGS__)
#define SYM_CALL_1(SYM_RVA, ...) SYM_CALL(FNTYPE_DEF_1, SYM_RVA, __VA_ARGS__)
#define SYM_CALL_2(SYM_RVA, ...) SYM_CALL(FNTYPE_DEF_2, SYM_RVA, __VA_ARGS__)
#define SYM_CALL_3(SYM_RVA, ...) SYM_CALL(FNTYPE_DEF_3, SYM_RVA, __VA_ARGS__)
#define SYM_CALL_4(SYM_RVA, ...) SYM_CALL(FNTYPE_DEF_4, SYM_RVA, __VA_ARGS__)
#define SYM_CALL_5(SYM_RVA, ...) SYM_CALL(FNTYPE_DEF_5, SYM_RVA, __VA_ARGS__)
#define SYM_CALL_6(SYM_RVA, ...) SYM_CALL(FNTYPE_DEF_6, SYM_RVA, __VA_ARGS__)
#define SYM_CALL_7(SYM_RVA, ...) SYM_CALL(FNTYPE_DEF_7, SYM_RVA, __VA_ARGS__)
#define SYM_CALL_8(SYM_RVA, ...) SYM_CALL(FNTYPE_DEF_8, SYM_RVA, __VA_ARGS__)
#define SYM_CALL_9(SYM_RVA, ...) SYM_CALL(FNTYPE_DEF_9, SYM_RVA, __VA_ARGS__)
#define SYM_CALL_10(SYM_RVA, ...) SYM_CALL(FNTYPE_DEF_10, SYM_RVA, __VA_ARGS__)
#define SYM_CALL_11(SYM_RVA, ...) SYM_CALL(FNTYPE_DEF_11, SYM_RVA, __VA_ARGS__)
#define SYM_CALL_12(SYM_RVA, ...) SYM_CALL(FNTYPE_DEF_12, SYM_RVA, __VA_ARGS__)
#define SYM_CALL_13(SYM_RVA, ...) SYM_CALL(FNTYPE_DEF_13, SYM_RVA, __VA_ARGS__)
#define SYM_CALL_14(SYM_RVA, ...) SYM_CALL(FNTYPE_DEF_14, SYM_RVA, __VA_ARGS__)
#define SYM_CALL_15(SYM_RVA, ...) SYM_CALL(FNTYPE_DEF_15, SYM_RVA, __VA_ARGS__)