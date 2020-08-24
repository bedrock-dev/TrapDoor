cmake_minimum_required(VERSION 3.17)
project(TrapDoor)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_library (TrapDoor SHARED
        entity/Actor.h
        block/Block.h
        common/Common.h
        lib/detours.h
        lib/detver.h
        dllmain.cpp
        lib/framework.h
        lib/mod.cpp
        lib/mod.h
        lib/pch.cpp
        lib/pch.h
        spawn/Spawn.h
        lib/SymHook.h
        Tools.h
        village/Village.h
        tools/MessageBuilder.cpp
        common/Vec3.h common/BlockPos.h common/AABB.h
        tick/Tick.h
        commands/Shell.cpp commands/Shell.h entity/ActorHook.h tick/TickHook.h tools/MathTool.h tools/Particle.h tools/Message.h village/VillagerHook.h)
