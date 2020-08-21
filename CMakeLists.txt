cmake_minimum_required(VERSION 3.17)
project(TrapDoor)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_library (TrapDoor SHARED
        Actor.h
        Block.h
        Cons.h
        detours.h
        detver.h
        dllmain.cpp
        framework.h
        mod.cpp
        mod.h
        pch.cpp
        pch.h
        Shell.h
        Spawn.h
        SymHook.h
        Tick.h
        Tools.h
        Village.h)
