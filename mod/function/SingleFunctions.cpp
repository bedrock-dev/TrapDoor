//
// Created by xhy on 2020/12/23.
//

#include "BDSMod.h"
#include "TrapdoorMod.h"
#include "lib/SymHook.h"
#include "lib/mod.h"

namespace mod {
using namespace SymHook;

THook(void, MSSYM_B1QA7explodeB1AA9ExplosionB2AAA7QEAAXXZ, void *exp) {
  auto modInstance = trapdoor::bdsMod->asInstance<mod::TrapdoorMod>();
  if (!modInstance->getSingFunction().preventExplosion)
    original(exp);
}

/**
 *  SYM_CALL(
            void(*)(BlockSource * self,const BlockPos *pos),
            MSSYM_B1QE17updateNeighborsAtB1AE11BlockSourceB2AAE17QEAAXAEBVBlockPosB3AAAA1Z,
            this, pos
    );
 */

THook(
    void,
    MSSYM_B1QE17updateNeighborsAtB1AE11BlockSourceB2AAE17QEAAXAEBVBlockPosB3AAAA1Z,
    trapdoor::BlockSource *source, trapdoor::BlockPos *pos) {
  auto modInstance = trapdoor::bdsMod->asInstance<mod::TrapdoorMod>();
  if (!modInstance->getSingFunction().preventNCUpdate)
    original(source, pos);
}

// 0X8AC060
constexpr uint64_t Continaer_can_open = 0X8AC060;
THook(bool, Continaer_can_open, void *container, void *bs) {
  auto modInstance = trapdoor::bdsMod->asInstance<mod::TrapdoorMod>();
  if (modInstance->getSingFunction().noConatinerObstruct) {
    return true;
  } else {
    return original(container, bs);
  }
}

/*
0X7425E0
public: virtual void __cdecl Container::removeItem(int,int) __ptr64
?removeItem@Container@@UEAAXHH@Z
*/
constexpr uint64_t Continaer_remove_item = 0X7425E0;
THook(void, Continaer_remove_item, void *container, int slot, int count) {
  auto modInstance = trapdoor::bdsMod->asInstance<mod::TrapdoorMod>();
  if (!modInstance->getSingFunction().noContainerCost) {
    original(container, slot, count);
  }
}

/*
0XA17390
public: bool __cdecl BlockSource::mayPlace(class Block const & __ptr64,class
BlockPos const & __ptr64,unsigned char,class Actor * __ptr64,bool) __ptr64
?mayPlace@BlockSource@@QEAA_NAEBVBlock@@AEBVBlockPos@@EPEAVActor@@_N@Z
*/

constexpr uint64_t BlockSource_mayPlace = 0XA17390;
THook(bool, BlockSource_mayPlace, void *bs, void *block, void *p,
      unsigned char face, void *placer, bool ignoreEntity) {

  auto modInstance = trapdoor::bdsMod->asInstance<mod::TrapdoorMod>();
  auto level = modInstance->getSingFunction().forceBuild;
  if (level == 1)
    return original(bs, block, p, face, placer, true);
  if (level == 2)
    return true;
  return original(bs, block, p, face, placer, ignoreEntity);
}

/*

0X1CC520
public: float __cdecl Core::Random::nextGaussian(void) __ptr64
?nextGaussian@Random@Core@@QEAAMXZ
*/

constexpr uint64_t Random_nextGaussian = 0X1CC520;
THook(float, Random_nextGaussian, void *random) {
  auto modInstance = trapdoor::bdsMod->asInstance<mod::TrapdoorMod>();
  int gauss = modInstance->getSingFunction().gaussRnd;
  if (gauss <= 0) {
    return 0;
  }
  return original(random) / gauss;
}

} // namespace mod