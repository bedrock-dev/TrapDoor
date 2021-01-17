cmake_minimum_required(VERSION 3.17)
project(mod)
set(CMAKE_CXX_STANDARD 17)
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    add_compile_options(/wd4828 /wd4819 /EHsc /utf-8)
else ()
    message(this project don't support GNU gcc or clang,please use MSVC instead)
endif ()
set(MOD_API_NAME trapDoorAPI)

add_library(${MOD_API_NAME} STATIC
        api/BDSMod.cpp
        api/block/Block.cpp
        api/block/BlockLegacy.cpp
        api/block/BlockSource.cpp
        api/commands/CommandNode.cpp
        api/commands/Command.cpp
        api/commands/CommandManager.cpp
        api/commands/ArgHolder.cpp
        api/entity/Actor.cpp
        api/entity/Item.cpp
        api/entity/PlayerInventory.cpp
        api/entity/PlayerBuffer.cpp
        api/graphics/Particle.cpp
        api/graphics/AABB.h
        api/graphics/BlockPos.cpp
        api/graphics/Vec3.cpp
        api/graphics/Graphics.cpp
        api/graphics/BlockPos.cpp
        api/world/Biome.cpp
        api/world/Dimension.cpp
        api/world/Level.cpp
        api/tools/DirtyLogger.cpp
        api/tools/Message.cpp
        api/tools/MsgBuilder.cpp
        api/tools/ThreadPool.h
        api/world/LevelChunk.cpp
        "api/tools/noncopyable .h")
target_include_directories(${MOD_API_NAME}
        PUBLIC
        api
        api/block
        api/commands
        api/entity
        api/graphics
        api/world
        api/lib
        api/tools
        )

target_link_libraries(${MOD_API_NAME} ${PROJECT_SOURCE_DIR}/api/lib/detours.lib)
target_link_libraries(${MOD_API_NAME} ${PROJECT_SOURCE_DIR}/api/lib/sqlite3.lib)



set(MOD_NAME trapdoor-mod)
add_library(${MOD_NAME}
        SHARED
        mod/dllmain.cpp
        mod/TrapdoorMod.cpp
        mod/function/Explosion.cpp
        mod/hopper/HopperCounter.cpp
        mod/config/ConfigManager.cpp
        mod/village/Village.cpp
        mod/tick/GameTick.cpp
        mod/spawn/HsaManager.cpp
        mod/tick/SimpleProfiler.cpp
        mod/tick/ActorProfiler.cpp
        mod/tick/BlockActorProfiler.cpp
        mod/spawn/SpawnHelper.cpp
        mod/spawn/SpawnAnalyzer.cpp
        mod/function/BlockRotationHelper.cpp
        mod/player/PlayerFunction.cpp
        mod/player/SimpleBuilder.cpp
        mod/spawn/SlimeChunkHelper.cpp
        mod/player/PlayerStatisticManager.cpp
        mod/player/Player.cpp
        mod/function/BackupHelper.cpp
        mod/os/process_stat.cpp
        mod/village/POIInstance.cpp
        )

target_include_directories(
        ${MOD_NAME}
        PUBLIC
        mod
        mod/os
        mod/config
        mod/hopper
        mod/spawn
        mod/function
        mod/village
        mod/tick
        mod/player
        api
        api/block
        api/commands
        api/entity
        api/graphics
        api/world
        api/lib
        api/tools
)

target_link_libraries(${MOD_NAME} ${MOD_API_NAME})

