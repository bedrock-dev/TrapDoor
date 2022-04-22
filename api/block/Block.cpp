//
// Created by xhy on 2020/8/26.
//
#include "Block.h"
#include "Offset.h"
#include "block/BlockLegacy.h"
#include "lib/SymHook.h"
#include "lib/mod.h"
#include "tools/CastHelper.h"
#include "tools/DirtyLogger.h"
#include "tools/Message.h"
#include <vector>

namespace trapdoor {
using namespace SymHook;

//获取方块legacy
BlockLegacy *Block::getLegacy() {
  return SYM_CALL(
      BlockLegacy * (*)(Block * block),
      MSSYM_B1QE14getLegacyBlockB1AA5BlockB2AAE19QEBAAEBVBlockLegacyB2AAA2XZ,
      this);
}

//获取方块名字
std::string Block::getName() {
  std::string debugStr;
  SYM_CALL(
      void (*)(void *block, std::string &),
      MSSYM_B1QE13toDebugStringB1AA5BlockB2AAA4QEBAB1QA2AVB2QDA5basicB1UA6stringB1AA2DUB2QDA4charB1UA6traitsB1AA1DB1AA3stdB2AAA1VB2QDA9allocatorB1AA1DB1AA12B2AAA3stdB2AAA2XZ,
      this, debugStr);
  // remove "name: "
  return debugStr.erase(0, 6);
}

//是否是空气
bool Block::isAir() { return this->getLegacy()->getBlockID() == AIR; }

//获取特殊值
int Block::getVariant() {

  return *offset_cast<char *>(this, off::BLOCK_GET_VARIANT);
}

Block *BlockActor::getBlock() {
  //*(this + 2)
  // return nullptr;
  return *reinterpret_cast<Block **>(reinterpret_cast<VA>(this) + 16);
  // return (Block *)*((char *)this + 2);
}

//获取方块实体的位置
BlockPos *BlockActor::getPosition() {
  return offset_cast<BlockPos *>(this, off::BLOCKSOURCE_GET_POSITION);
  // return reinterpret_cast<BlockPos *>(reinterpret_cast<VA>(this) + 44);
}

} // namespace trapdoor
