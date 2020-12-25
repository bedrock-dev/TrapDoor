#pragma once
#include "Windows.h"
#include "detours.h"
#include "detver.h"
#include <iostream>
using VA = unsigned __int64;
using RVA = unsigned long int;

template<typename T>
auto Hook(T *p, T f) {
    int error = DetourTransactionBegin();
    if (error != NO_ERROR) {
        return "Hook: DetourTransactionBegin Error";
    }
    error = DetourUpdateThread(GetCurrentThread());
    if (error != NO_ERROR) {
        return "Hook: DetourUpdateThread Error";
    }
    error = DetourAttach((PVOID * )
    p, (PVOID)
    f);
    if (error != NO_ERROR) {
        return "Hook: DetourAttach Error";
    }
    error = DetourTransactionCommit();
    if (error != NO_ERROR) {
        return "Hook: DetourTransactionCommit Error";
    }
    return static_cast<const char *>(nullptr);
}

template<typename T>
auto UnHook(T *p, T f) {
    int error = DetourTransactionBegin();
    if (error != NO_ERROR) {
        return "UnHook: DetourTransactionBegin Error";
    }
    error = DetourUpdateThread(GetCurrentThread());
    if (error != NO_ERROR) {
        return "UnHook: DetourUpdateThread Error";
    }
    error = DetourDetach((PVOID * )
    p, (PVOID)
    f);
    if (error != NO_ERROR) {
        return "UnHook: DetourDetach Error";
    }
    error = DetourTransactionCommit();
    if (error != NO_ERROR) {
        return "UnHook: DetourTransactionCommit Error";
    }
    return static_cast<const char *>(nullptr);
}

struct RegisterStaticHook {

    RegisterStaticHook(RVA sym, void *hook, void **org) {
        auto base = reinterpret_cast<VA>(GetModuleHandle(NULL));
        *org = reinterpret_cast<void *>(base + sym);
        auto ret = Hook<void *>(org, hook);
        if (ret != nullptr)
            std::cout << "[Error]" << " " << ret << std::endl;
    }

    // workaround for a warning
    template<typename T>
    RegisterStaticHook(RVA sym, T hook, void **org) {
        union {
            T a;
            void *b;
        } hookUnion;
        hookUnion.a = hook;
        RegisterStaticHook(sym, hookUnion.b, org);
    }
};

#define _TInstanceHook(class_inh, pclass, iname, sym, ret, ...)                                                                                  \
  struct _TInstanceHook_##iname class_inh {                                                                                                          \
    static ret (_TInstanceHook_##iname::*_original)(__VA_ARGS__);                                                                                           \
    template <typename... Params> static ret original(pclass *_this, Params &&... params) {                                                          \
      return (((_TInstanceHook_##iname *)_this)->*_original)(std::forward<Params>(params)...);                                                       \
    }                                                                                                                                                \
    ret _hook(__VA_ARGS__);                                                                                                                                 \
  };                                                                                                                                                 \
  static RegisterStaticHook _TRInstanceHook_##iname(sym, &_TInstanceHook_##iname::_hook, (void **)&_TInstanceHook_##iname::_original);              \
  ret (_TInstanceHook_##iname::*_TInstanceHook_##iname::_original)(__VA_ARGS__);                                                                            \
  ret _TInstanceHook_##iname::_hook(__VA_ARGS__)
#define _TInstanceDefHook(iname, sym, ret, type, ...)                _TInstanceHook( : public type, type, iname, sym, ret, __VA_ARGS__)
#define _TInstanceNoDefHook(iname, sym, ret, ...)                    _TInstanceHook(, void, iname, sym, ret, __VA_ARGS__)

#define _TStaticHook(pclass, iname, sym, ret, ...)                                                                                               \
  struct _TStaticHook_##iname pclass {                                                                                                               \
    static ret (*_original)(__VA_ARGS__);                                                                                                                   \
    template <typename... Params> static ret original(Params &&... params) { return (*_original)(std::forward<Params>(params)...); }                 \
    static ret _hook(__VA_ARGS__);                                                                                                                          \
  };                                                                                                                                                 \
  static RegisterStaticHook _TRStaticHook_##iname(sym, &_TStaticHook_##iname::_hook, (void **)&_TStaticHook_##iname::_original);                    \
  ret (*_TStaticHook_##iname::_original)(__VA_ARGS__);                                                                                                      \
  ret _TStaticHook_##iname::_hook(__VA_ARGS__)
#define _TStaticDefHook(iname, sym, ret, type, ...)                    _TStaticHook( : public type, iname, sym, ret, __VA_ARGS__)
#define _TStaticNoDefHook(iname, sym, ret, ...)                        _TStaticHook(, iname, sym, ret, __VA_ARGS__)

#define THook2(iname, ret, sym, ...)                                _TStaticNoDefHook(iname, sym, ret, __VA_ARGS__)
#define THook(ret, sym, ...)                                        THook2(sym, ret, sym, __VA_ARGS__)
#define TClasslessInstanceHook2(iname, ret, sym, ...)                _TInstanceNoDefHook(iname, sym, ret, __VA_ARGS__)
#define TClasslessInstanceHook(ret, sym, ...)                        TClasslessInstanceHook2(sym, ret, sym, args)
#define TInstanceHook2(iname, ret, sym, type, ...)                    _TInstanceDefHook(iname, sym, ret, type, __VA_ARGS__)
#define TInstanceHook(ret, sym, type, ...)                            TInstanceHook2(sym, ret, sym, type, __VA_ARGS__)
#define TStaticHook2(iname, ret, sym, type, ...)                    _TStaticDefHook(iname, sym, ret, type, __VA_ARGS__)
#define TStaticHook(ret, sym, type, ...)                            TStaticHook2(sym, ret, sym, type, __VA_ARGS__)

#define FNTYPE_DEF(...) VA (*)(__VA_ARGS__)
#define FNTYPE_DEF_0    FNTYPE_DEF()
#define FNTYPE_DEF_1    FNTYPE_DEF(VA)
#define FNTYPE_DEF_2    FNTYPE_DEF(VA,VA)
#define FNTYPE_DEF_3    FNTYPE_DEF(VA,VA,VA)
#define FNTYPE_DEF_4    FNTYPE_DEF(VA,VA,VA,VA)
#define FNTYPE_DEF_5    FNTYPE_DEF(VA,VA,VA,VA,VA)
#define FNTYPE_DEF_6    FNTYPE_DEF(VA,VA,VA,VA,VA,VA)
#define FNTYPE_DEF_7    FNTYPE_DEF(VA,VA,VA,VA,VA,VA,VA)
#define FNTYPE_DEF_8    FNTYPE_DEF(VA,VA,VA,VA,VA,VA,VA,VA)
#define FNTYPE_DEF_9    FNTYPE_DEF(VA,VA,VA,VA,VA,VA,VA,VA,VA)
#define FNTYPE_DEF_10    FNTYPE_DEF(VA,VA,VA,VA,VA,VA,VA,VA,VA,VA)
#define FNTYPE_DEF_11    FNTYPE_DEF(VA,VA,VA,VA,VA,VA,VA,VA,VA,VA,VA)
#define FNTYPE_DEF_12    FNTYPE_DEF(VA,VA,VA,VA,VA,VA,VA,VA,VA,VA,VA,VA)
#define FNTYPE_DEF_13    FNTYPE_DEF(VA,VA,VA,VA,VA,VA,VA,VA,VA,VA,VA,VA,VA)
#define FNTYPE_DEF_14    FNTYPE_DEF(VA,VA,VA,VA,VA,VA,VA,VA,VA,VA,VA,VA,VA,VA)
#define FNTYPE_DEF_15    FNTYPE_DEF(VA,VA,VA,VA,VA,VA,VA,VA,VA,VA,VA,VA,VA,VA,VA)

#define SYM_PTR(TYPE, SYM_RVA)                                        reinterpret_cast<TYPE>(reinterpret_cast<VA>(GetModuleHandle(NULL))+SYM_RVA)
#define SYM_CALL(TYPE, SYM_RVA, ...)                                SYM_PTR(TYPE, SYM_RVA)(__VA_ARGS__)
#define SYM_CALL_0(SYM_RVA, ...)                                    SYM_CALL(FNTYPE_DEF_0, SYM_RVA, __VA_ARGS__)
#define SYM_CALL_1(SYM_RVA, ...)                                    SYM_CALL(FNTYPE_DEF_1, SYM_RVA, __VA_ARGS__)
#define SYM_CALL_2(SYM_RVA, ...)                                    SYM_CALL(FNTYPE_DEF_2, SYM_RVA, __VA_ARGS__)
#define SYM_CALL_3(SYM_RVA, ...)                                    SYM_CALL(FNTYPE_DEF_3, SYM_RVA, __VA_ARGS__)
#define SYM_CALL_4(SYM_RVA, ...)                                    SYM_CALL(FNTYPE_DEF_4, SYM_RVA, __VA_ARGS__)
#define SYM_CALL_5(SYM_RVA, ...)                                    SYM_CALL(FNTYPE_DEF_5, SYM_RVA, __VA_ARGS__)
#define SYM_CALL_6(SYM_RVA, ...)                                    SYM_CALL(FNTYPE_DEF_6, SYM_RVA, __VA_ARGS__)
#define SYM_CALL_7(SYM_RVA, ...)                                    SYM_CALL(FNTYPE_DEF_7, SYM_RVA, __VA_ARGS__)
#define SYM_CALL_8(SYM_RVA, ...)                                    SYM_CALL(FNTYPE_DEF_8, SYM_RVA, __VA_ARGS__)
#define SYM_CALL_9(SYM_RVA, ...)                                    SYM_CALL(FNTYPE_DEF_9, SYM_RVA, __VA_ARGS__)
#define SYM_CALL_10(SYM_RVA, ...)                                    SYM_CALL(FNTYPE_DEF_10, SYM_RVA, __VA_ARGS__)
#define SYM_CALL_11(SYM_RVA, ...)                                    SYM_CALL(FNTYPE_DEF_11, SYM_RVA, __VA_ARGS__)
#define SYM_CALL_12(SYM_RVA, ...)                                    SYM_CALL(FNTYPE_DEF_12, SYM_RVA, __VA_ARGS__)
#define SYM_CALL_13(SYM_RVA, ...)                                    SYM_CALL(FNTYPE_DEF_13, SYM_RVA, __VA_ARGS__)
#define SYM_CALL_14(SYM_RVA, ...)                                    SYM_CALL(FNTYPE_DEF_14, SYM_RVA, __VA_ARGS__)
#define SYM_CALL_15(SYM_RVA, ...)                                    SYM_CALL(FNTYPE_DEF_15, SYM_RVA, __VA_ARGS__)


