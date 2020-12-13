cmake_minimum_required(VERSION 3.17)
project(TrapDoor)
set(CMAKE_CXX_STANDARD 17)
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    add_compile_definitions(-O3 -Wall)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    add_compile_options(/wd4828 /wd4819 /EHsc /utf-8)
endif ()
include_directories(.)

add_library(Trapdoor SHARED
        dllmain.cpp
        tools/MathTool.cpp
        tools/MsgBuilder.cpp
        graphics/Particle.cpp
        tools/Message.cpp
        lib/pch.cpp
        village/Village.cpp
        common/Trapdoor.cpp
        common/ConfigManager.cpp
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
        graphics/BlockPos.cpp
        graphics/Vec3.cpp
        entity/PlayerBuffer.cpp
        level/Biome.cpp
        level/Dimension.cpp
        tools/json.hpp
        tools/DirtyLogger.cpp
        common/RightClickManager.cpp
        entity/PlayerInventory.cpp
        graphics/Graphics.cpp
        )

target_link_libraries(Trapdoor ${PROJECT_SOURCE_DIR}/lib/detours.lib)

add_executable(Test
        test/testMain.cpp
        tools/DirtyLogger.cpp
        tools/json.hpp
        common/ConfigManager.cpp
        graphics/Vec3.cpp
        graphics/BlockPos.cpp
        graphics/Graphics.cpp
        )


