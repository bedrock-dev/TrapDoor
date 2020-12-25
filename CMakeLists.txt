cmake_minimum_required(VERSION 3.17)
set(DllName mod)
Set(MinecraftVersion 1.16.4)
set(buildType debug)
set(OutputName ${DllName}-${MinecraftVersion}-${buildType})
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
        api/entity/Player.cpp
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
        api/world/LevelChunk.cpp
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
        )

target_link_libraries(${MOD_API_NAME} ${PROJECT_SOURCE_DIR}/api/lib/detours.lib)


set(MOD_NAME trapdoor-mod)
add_library(${MOD_NAME}
        SHARED
        mod/dllmain.cpp
        mod/TrapdoorMod.cpp
        mod/single/Explosion.cpp
        mod/hopper/HopperCounter.cpp
        mod/config/ConfigManager.cpp
        mod/config/RightClickManager.cpp
        mod/village/Village.cpp
        mod/tick/GameTick.cpp
        )

target_include_directories(
        ${MOD_NAME}
        PUBLIC

        mod
        mod/config
        mod/hopper
        mod/spawn
        mod/single
        mod/village
        mod/tick
        api
        api/block
        api/commands
        api/entity
        api/graphics
        api/world
        api/lib

)


target_link_libraries(${MOD_NAME} ${MOD_API_NAME})

#add_library(${PROJECT_NAME} SHARED
#        dllmain.cpp
#        api/tools/MsgBuilder.cpp
#        api/graphics/Particle.cpp
#        api/tools/Message.cpp
#        api/lib/pch.cpp
#        mod/village/Village.cpp
#        api/BDSMod.cpp
#        mod/common/ConfigManager.cpp
#        mod/spawn/Spawn.cpp
#        api/entity/Actor.cpp
#        mod/tick/GameTick.cpp
#        api/level/Level.cpp
#        api/commands/Command.cpp
#        api/commands/Command.h
#        api/commands/ArgHolder.cpp
#        api/commands/CommandManager.cpp
#        api/commands/CommandNode.cpp
#        api/block/Block.cpp
#        api/entity/Item.cpp
#        mod/Hopper.cpp
#        api/entity/Player.cpp
#        api/graphics/BlockPos.cpp
#        api/graphics/Vec3.cpp
#        api/entity/PlayerBuffer.cpp
#        api/level/Biome.cpp
#        api/level/Dimension.cpp
#        api/tools/json.hpp
#        api/tools/DirtyLogger.cpp
#        mod/common/RightClickManager.cpp
#        api/entity/PlayerInventory.cpp
#        api/graphics/Graphics.cpp
#        api/block/BlockLegacy.cpp api/block/BlockLegacy.h api/block/BlockSource.cpp api/block/BlockSource.h mod/Trapdoor.cpp mod/Trapdoor.h)
#
#target_link_libraries(${PROJECT_NAME} api/lib/detours.lib)
#
#add_executable(ConfigTest mod/common/ConfigManager.cpp api/tools/DirtyLogger.cpp test/testMain.cpp)



