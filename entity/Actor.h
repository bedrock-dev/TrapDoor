

#ifndef TRAPDOOR_ACTOR_H
#define TRAPDOOR_ACTOR_H

#include "common/Vec3.h"
#include <vector>
#include <string>

/**
 * todo: need rewrite
 */
class BlockSource;

class Actor {
public:
    Vec3 *getPos();

    void getViewActor(Vec3 *vec3, float val);

    std::string getNameTag();

    BlockSource *getBlockSource();

};

class ActorDefinitionIdentifier {
public:
    std::string getName();
};

std::string actorIDtoString(char *actorID);

std::vector<std::string> getActorText(void *actor);

void sendMobInfo();

void startSpawnCounter();

void endSpawnerCounter();

void spawnAnalysis(std::string &type);

std::string getActorName(void *actor);

#endif
