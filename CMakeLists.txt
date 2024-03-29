cmake_minimum_required(VERSION 3.17)
project(mod)
set(CMAKE_CXX_STANDARD 17)
#因为ABI原因这个项目只能msvc编译
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    add_compile_options(/wd4828 /wd4819 /EHsc /utf-8)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Zi")
    set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /DEBUG /OPT:REF /OPT:ICF")

else ()
    message(this project don't support GNU gcc, please use MSVC instead)
endif ()
set(CMAKE_BUILD_TYPE release)
set(MOD_API_NAME trapdoor)


add_library(${MOD_API_NAME} STATIC
        api/BDSMod.cpp
        api/block/Block.cpp
        api/block/BlockLegacy.cpp
        api/block/BlockSource.cpp
        api/block/VanillaBlockType.cpp
        api/commands/CommandNode.cpp
        api/commands/Command.cpp
        api/commands/CommandManager.cpp
        api/commands/ArgHolder.cpp
        api/entity/Actor.cpp
        api/entity/Item.cpp
        api/entity/PlayerBuffer.cpp
        api/graphics/Particle.cpp
        api/graphics/AABB.h
        api/graphics/BlockPos.cpp
        api/graphics/Vec3.cpp
        api/graphics/BlockPos.cpp
        api/world/Biome.cpp
        api/world/Dimension.cpp
        api/world/Level.cpp
        api/tools/DirtyLogger.cpp
        api/tools/Message.cpp
        api/tools/MsgBuilder.cpp
        api/tools/ThreadPool.h
        api/language/I18nManager.cpp
        api/tools/CastHelper.h

        api/Offset.h
        )

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
        api/language
        api/language/lang
        )

target_link_libraries(${MOD_API_NAME} ${PROJECT_SOURCE_DIR}/api/lib/detours.lib)

####################这里是具体功能##########################
set(TRAPDOOR_VERSION 0.11)
set(MCBE_VERSION 1.18.33.04)
set(BETA OFF)
set(TEST_NUMBER 1)
add_definitions(-DTD_VERSION="${TRAPDOOR_VERSION}")
add_definitions(-DMC_VERSION="${MCBE_VERSION}")
if (${BETA} STREQUAL "ON")
    add_definitions(-DBETA)
    set(MOD_NAME ${MOD_API_NAME}-${TRAPDOOR_VERSION}-${MCBE_VERSION}-test-${TEST_NUMBER})
else ()
    set(MOD_NAME ${MOD_API_NAME}-${TRAPDOOR_VERSION}-${MCBE_VERSION})
endif ()

add_library(${MOD_NAME}
        SHARED
        mod/dllmain.cpp
        mod/TrapdoorMod.cpp
        mod/function/SingleFunctions.cpp
        mod/function/HopperCounter.cpp
        mod/config/ConfigManager.cpp
        mod/village/Village.cpp
        mod/tick/GameTick.cpp
        mod/spawn/HsaManager.cpp
        mod/tick/SimpleProfiler.cpp
        mod/tick/ActorProfiler.cpp
        mod/spawn/SpawnHelper.cpp
        mod/function/BlockRotationHelper.cpp
        mod/function/FunctionCommands.cpp
        mod/player/PlayerFunction.cpp
        mod/function/SimpleBuilder.cpp
        mod/spawn/SlimeChunkHelper.cpp
        mod/function/BackupHelper.cpp
        mod/os/process_stat.cpp
        mod/village/POIInstance.cpp
        mod/eval/Eval.cpp
        mod/test/TrapdoorTest.cpp
        mod/fakePlayer/FakePlayerClient.cpp
        mod/fakePlayer/easywsclient.cpp
        )

target_include_directories(
        ${MOD_NAME}
        PUBLIC
        mod
        mod/os
        mod/config
        mod/test
        mod/spawn
        mod/function
        mod/village
        mod/tick
        mod/player
        mod/dirtyLitematica
        mod/eval
        mod/fakePlayer

        api
        api/block
        api/commands
        api/entity
        api/graphics
        api/world
        api/lib
        api/tools
        api/language
        api/language/lang
)

target_link_libraries(${MOD_NAME} ${MOD_API_NAME})

