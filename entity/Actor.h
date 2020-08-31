#pragma once

#include "common/Common.h"
#include "lib/mod.h"
#include "lib/SymHook.h"
#include "spawn/Spawn.h"
#include <vector>
#include <map>
#include "../spawn/Spawn.h"
#include "tools/Message.h"

/**
 * todo: need rewrite
 */
namespace spawn {
    class Actor {

    };


    Vec3 *getPos(void *actor);

    std::string actorIDtoString(char *actorID);

    std::vector<std::string> getActorText(void *actor);

    void sendMobInfo();

    void startSpawnCounter();

    void endSpawnerCounter();

    void spawnAnalysis(std::string &type);

    std::string getActorName(void *actor);


}

