cmake_minimum_required(VERSION 3.17)
project(TrapDoor)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "/wd4819 /EHsc")
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
        tick/GameTick.cpp
        level/Level.cpp
        commands/Command.cpp
        commands/Command.h
        commands/ArgHolder.cpp
        commands/CommandManager.cpp
        commands/CommandNode.cpp
        block/Block.cpp
        entity/Item.cpp
        block/Hopper.cpp
        entity/Player.cpp
        common/BlockPos.cpp
        common/Vec3.cpp
        entity/PlayerSpace.cpp
        level/Biome.cpp
        level/Dimension.cpp
        )


add_executable(Test
        test/testMain.cpp
        commands/ArgHolder.cpp
        )
