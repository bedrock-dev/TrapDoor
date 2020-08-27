cmake_minimum_required(VERSION 3.17)
project(TrapDoor)

set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_FLAGS "/IGNORE:C4819")
include_directories(.)
add_library(TrapDoor SHARED
        dllmain.cpp
        tools/MathTool.cpp
        tools/MessageBuilder.cpp
        tools/Particle.cpp
        tools/Message.cpp
        lib/pch.cpp
        lib/mod.cpp
        village/Village.cpp
        common/Common.cpp
        spawn/Spawn.cpp
        entity/Actor.cpp
        tick/Tick.cpp
        commands/Shell.cpp
        commands/Shell.h
        block/Block.cpp commands/VanillaCommand.cpp commands/VanillaCommand.h)
