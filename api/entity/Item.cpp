//
// Created by xhy on 2020/8/29.
//

#include "Item.h"
#include "Offset.h"
#include "PlayerBuffer.h"
#include "block/Block.h"
#include "lib/SymHook.h"
#include "lib/mod.h"
#include "tools/CastHelper.h"
#include "tools/DirtyLogger.h"
#include "tools/Message.h"
#include "tools/MsgBuilder.h"
#include <fstream>
#include <string>

namespace trapdoor {
using namespace SymHook;
namespace {
std::unordered_map<std::string, std::string> item_name_map;
}
std::string ItemStackBase::getItemName() {
  std::string name;
  SYM_CALL(
      void (*)(ItemStackBase *, std::string *),
      MSSYM_B1QA7getNameB1AE13ItemStackBaseB2AAA4QEBAB1QA2AVB2QDA5basicB1UA6stringB1AA2DUB2QDA4charB1UA6traitsB1AA1DB1AA3stdB2AAA1VB2QDA9allocatorB1AA1DB1AA12B2AAA3stdB2AAA2XZ,
      this, &name);
  return name;
}

int ItemStackBase::getNum() {
  return *offset_cast<char *>(this, off::ITEM_GET_NUM);
}

void InitItemNameMap() {
  const std::string bds_lang_file_path =
      ".\\resource_packs\\vanilla\\texts\\zh_CN.lang";
  std::ifstream input(bds_lang_file_path);
  if (!input.is_open()) {
    L_WARNING("can not read bds lang file");
    return;
  }
  std::string line;
  while (getline(input, line)) {
    if (line.find("item.") == 0 || line.find("tile.") == 0) {
      // item.iron_hoe.name=铁锄	#
      auto p1 = line.find("=");
      auto p2 = line.find('\t');
      auto key = line.substr(0, p1);
      auto name = line.substr(p1 + 1, p2 - p1);
      name.erase(std::remove(name.begin(), name.end(), '\t'), name.end());
      item_name_map[key] = name;
    }
  }
}

std::string GetItemLocalName(const std::string &name) {
  LCID localeID = GetUserDefaultLCID();
  unsigned short lang = localeID & 0xFF;
  if (lang != LANG_CHINESE) {
    return name;
  }
  auto key = name;
  for (auto &i : key) {
    if (i == ' ')
      i = '_';
    if (i <= 'Z' && i >= 'A')
      i -= ('Z' - 'z');
  }

  auto key1 = "item." + key + ".name";
  auto iter = item_name_map.find(key1);
  if (iter != item_name_map.end()) {
    return iter->second;
  }

  auto key2 = "tile." + key + ".name";
  auto iter2 = item_name_map.find(key2);
  if (iter2 != item_name_map.end()) {
    return iter2->second;
  }
  return name;
}
} // namespace trapdoor

using namespace SymHook;
//右键代理类
THook(
    void,
    MSSYM_B1QA5useOnB1AA4ItemB2AAA4QEBAB1UE14NAEAVItemStackB2AAA9AEAVActorB2AAA7HHHEMMMB1AA1Z,
    void *item, trapdoor::ItemStackBase *itemStack, trapdoor::Actor *player,
    int x, int y, int z, unsigned int facing, float dx, float dy, float dz) {
  uint64_t gameTick = player->getLevel()->getGameTick();
  // L_INFO("%.2f %.2f %.2f,tick =  %llu", x, y, z, gameTick);
  trapdoor::RightClickCache targetCache{gameTick, x, y, z};

  auto &playerCache =
      trapdoor::bdsMod->getPlayerBuffer()[player->getNameTag()].rightClickCache;
  //下面用一个简单的缓存 + 判定消除重复点击
  if (playerCache != targetCache) {
    //响应右键事件
    trapdoor::BlockPos pos(x, y, z);
    const trapdoor::Vec3 vec3(dx, dy, dz);
    trapdoor::bdsMod->useOnHook(player, itemStack->getItemName(), pos, facing,
                                vec3);
    playerCache = targetCache;
  }
  original(item, itemStack, player, x, y, z, facing, dx, dy, dz);
}
